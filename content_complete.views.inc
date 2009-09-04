<?php
// $Id$
/**
 * Implementation of hook_views_data()
 */
function content_complete_views_data() {
  $data['content_complete']['table']['group']  = t('Node');
  
  $data['content_complete']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['content_complete']['completeness'] = array(
    'title' => t('Completeness'),
    'help' => t('The completeness of the node (define by Content Complete).'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
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

  return $data;
}