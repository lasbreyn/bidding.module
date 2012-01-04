<?php
// $Id$

/**
 * @file
 * Administration page callback for job_bidding module.
 */

/**
 * Form builder. Configure bids.
 *
 * @ingroup forms
 * @see system_settings_forms().
 */
function job_auction_admin_settings() {
  // Get an array of node types with internal names as keys and
  // "friendly names" as values. E.g.,
  // array('page' => 'page', 'story' => 'story')
  $options = node_get_types('names');
  
  $form['auction_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Users may bid these content types'),
    '#options' => $options,
    '#default_value' => variable_get('auction_node_types', array('')),
    '#description' => t('Bid fields will be added to these content types to place bids.'),
  );
  
$form['auction_days'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Default Auction Length'),
    '#description'   => t('When a new auction is created, the expiry date will default to this number of days into the future.'),
    '#default_value' => variable_get('auction_days', 1),
    '#size'          => 10,
    '#maxlength'     => 2,
    '#required'      => TRUE,
  );

  $form['auction_fixed'] = array(
    '#type'          => 'select',
    '#title'         => t('Fixed expire date'),
    '#description'   => t('If yes, users wont be able to change the expiration date'),
    '#default_value' => variable_get('auction_fixed', TRUE),
    '#options'       => array('No', 'Yes'),
    '#required'      => TRUE,
  ); 
  $form['auction_default_currency'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Default currency'),
    '#default_value'  => variable_get('auction_default_currency', ''),
    '#description'    => t('Since there will be no payments made, provide a field to enter currency and provide a default to $(USD).'),
    '#size'			  => 10,
    '#maxlength'	  => 6,
    '#required'       => TRUE,
  );
  return system_settings_form($form);
  
}

/**
 * Validate the job auction configuration form.
 */
function job_auction_admin_settings_validate($form, $form_state) {
	$limit = $form_state['values']['auction_days'];
	if (!is_numeric($limit)) {
		form_set_error('auction_days', t('Please enter a number.'));
	}
}