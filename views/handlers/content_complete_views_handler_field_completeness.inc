<?php
// $Id$

/**
 *  @file
 *  This defines a view that outputs the completeness value of a node.
 */

class content_complete_views_handler_field_completeness extends views_handler_field_custom {

  function option_definition() {
    $options = parent::option_definition();

    $options['prefix'] = array('default' => '', 'translatable' => TRUE);
    $options['suffix'] = array('default' => '', 'translatable' => TRUE);
    $options['display_as'] = array('default' => 'numeric', 'translatable' => TRUE);
    
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $form['display_as'] = array(
      '#type' => 'select',
      '#title' => t('Display As'),
      '#options' => array(
    	  'numeric' => t('Numeric Value'),
    	  'bar' => t('Bar'),
    	),
      '#default_value' => $this->options['display_as'],
      '#description' => t('Choose how to display the number of runs.'),
    );
    
    $form['advanced_settings'] = array(
      '#title' => t('Advanced Settings'),
      '#type' => 'fieldset',
      '#description' => t('This settings will be applied if the data will be shown in "Numeric" or "Percentage" form.'),
      '#collapsible' => TRUE, 
      '#collapsed' => FALSE,   
    );
    
    $form['advanced_settings']['prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Prefix'),
      '#size' => 30,
      '#default_value' => $this->options['prefix'],
      '#description' => t('Text to put before the number of runs.'),
    );
    $form['advanced_settings']['suffix'] = array(
      '#type' => 'textfield',
      '#title' => t('Suffix'),
      '#size' => 30,
      '#default_value' => $this->options['suffix'],
      '#description' => t('Text to put after the number of runs.'),
    );  
  }
	
  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field($this->table_alias, $this->real_field);
    $this->add_additional_fields();
  }	
	
  function render($values) {    
    $data['percent'] = $values->content_complete_completeness;
    switch ($this->options['display_as']) {
      default:
      case 'numeric':
    	  return check_plain($this->options['advanced_settings']['prefix'] . $data['percent'] . $this->options['advanced_settings']['suffix']);
    	break;
    	case 'bar':
    	  return theme('content_complete_profile_percent_complete', $data);
      break;    	
    }
  }
  
}
