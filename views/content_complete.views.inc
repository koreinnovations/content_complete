<?php
// $Id$

/**
 *  @file
 *  Views integration.
 */

/**
 * Implementation of hook_views_data()
 */
function content_complete_views_data() {
  $data['content_complete']['table']['group']  = t('Content Complete');
  
  $data['content_complete']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['content_complete']['completeness'] = array(
    'title' => t('Completeness'),
    'help' => t('The completeness of the node.'),
    'field' => array(
      'handler' => 'content_complete_views_handler_field_completeness',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'title', // the field to display in the summary.
      'numeric' => TRUE,
    ),
    // Information for accepting a nid as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a nid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['content_complete']['content_type'] = array(
    'title' => t('Content type'),
    'help' => t('Whether or not the content type is used for Content Complete.'),
    'filter' => array(
      'handler' => 'content_complete_views_handler_filter_content_type',
      'label' => t('Is Content Complete enabled content type'),
    ),
  );
  
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function content_complete_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'content_complete') .'/views/handlers',
    ),
    'handlers' => array(
      // field handlers
      'content_complete_views_handler_field_completeness' => array(
        'parent' => 'views_handler_field_custom',
      ),
      
      // filter handlers
      'content_complete_views_handler_filter_content_type' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      
    ),
  );
}
