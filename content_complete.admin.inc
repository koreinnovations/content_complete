<?php
// $Id$ 

/** 
 *@file 
 *Administration page callbacks for the content_complete module. 
 */

/**
 * Menu Callback Function
 *  Build output of the content_complete module settings which allows the
 *  administrator to tag specific profile fields which will be 
 *  used to determine the completion of a users profile.
 */
function content_complete_admin_settings() {
  $header = t('Select one or more content types with their fields to check for completeness.');
  $form = drupal_get_form('content_complete_admin_settings_form');
  return $header . $form;
}

/**
 * Admin settings form
 */
function content_complete_admin_settings_form() {
  // get all content types
  $types = node_get_types('names');
  
  $form = array(
     
  );
  foreach ($types as $content_type => $content_name) {
    $data = content_complete_admin_settings_form_data($content_type);
    $type_set = (empty($data['default']['type'])) ? FALSE : TRUE;    

    $id = $content_type;
    
    $form[$id] = array(
      '#title' => $content_name, '#type' => 'fieldset', // '#description' => 'Select CCK content type',
    '#collapsible' => TRUE, '#collapsed' => ! $type_set 
    );
    
    $form[$id]['content'] = array(
      '#type' => 'checkboxes', '#description' => t('If this content type is selected, completeness checks will be run on the fields selected below.'), '#options' => array(
      $content_type => t($content_type) 
    ), '#default_value' => $data['default']['type'] 
    );
    
    $form[$id]['fields'] = array(
      '#type' => 'checkboxes', '#description' => t('Selected fields will be used in the check for completeness.'), '#options' => $data['options'], '#default_value' => $data['default']['fields'] 
    );
  
  }
  
  $form['submit'] = array(
    '#type' => 'submit', '#value' => t('Save') 
  );
  
  $form['#tree'] = TRUE; // return nested array of fields	
  

  return $form;
}

/**
 * Admin settings form submit
 */
function content_complete_admin_settings_form_submit($form, &$form_state) {
  if (is_array($form_state['values']) && ! empty($form_state['values'])) {
    db_query("DELETE FROM {content_complete}");
    foreach ($form_state['values'] as $key => $value) {
      
      if (is_array($value) && isset($value['content']) && isset($value['fields'])) {
        $content = array_filter($value['content']);
        $fields = array_filter($value['fields']);
        
        if (! empty($content) && ! empty($fields)) {
          $type = key($content);
          foreach ($fields as $field) {
            db_query("INSERT INTO {content_complete} VALUES ('%s', '%s')", $type, $field);
          }
        }
      
      }
    }
    
    drupal_set_message("Your settings have been saved.");
  }
}

function content_complete_admin_settings_form_data($content_type) {
  
  /**
   * Get the fields for this content type
   */
  $fields = content_complete_get_fields($content_type);
  
  /**
   * Format for presentation
   */
  $options = array(
     
  );
  foreach ($fields as $field_name => $field_data) {
    $key = $field_name;
    $label = $field_data['label'] ." <span class='description'>". $field_name ."</span>";
    $options[$field_name] = $label;
  }
  
  /**
   * Put the default values
   */
  $default_type = $default_fields = array(
     
  );
  $tagged_fields = content_complete_get_tagged_fields($content_type);
  if (! empty($tagged_fields)) {
    $default_type[] = $content_type;
    foreach ($tagged_fields as $tagged_field) {
      $default_fields[] = $tagged_field;
    }
  }
  
  $data['options'] = $options;
  $data['default']['type'] = $default_type;
  $data['default']['fields'] = $default_fields;
  
  return $data;
}
