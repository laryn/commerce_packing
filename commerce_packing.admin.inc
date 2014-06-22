<?php
/**
 * @file
 * Handles admin settings page for Commerce Packing module.
 */

/**
 * Form builder.
 */
function commerce_packing_overview_form($form, &$form_state) {
  $form['#tree'] = TRUE;
  $boxes = variable_get('commerce_packing_package_sizes','');
   if(empty($form_state['num_boxes'])) {
     $form_state['num_boxes'] = count($boxes) + 1;  
   }
   
   $form['sizes']['#prefix'] = '<div id="boxes-fieldset-wrapper">';
   $form['sizes']['#suffix'] = '</div>';
   
   for($i=0; $i < $form_state['num_boxes']; $i++) {
     $form['sizes'][$i] = array(
       '#type' => 'fieldset',
       '#title' => t('Package'),
       '#attributes' => array('class'=> array('physical-dimensions-textfields')),
       '#attached' => array('css' => array(drupal_get_path('module', 'physical') . '/theme/physical.css')),
    );

    foreach (physical_dimensions() as $key => $dimension) {
       $form['sizes'][$i][$key] = array(
         '#type' => 'textfield',
         '#title' => $dimension['name'],
         '#size' => 15,
         '#maxlength' => 16,
         '#field_suffix' => '&times;',
         '#prefix' => '<div class="physical-dimension-form-item">',
         '#suffix' => '</div>',
       );
       
       if(isset($boxes[$i][$key])) {
         $form['sizes'][$i][$key]['#default_value'] = $boxes[$i][$key];
       }
    }
    unset( $form['sizes'][$i][$key]['#field_suffix']);
   
    $form['sizes'][$i]['unit'] = array(
        '#type' => 'select',
        '#options' => physical_dimension_unit_options(FALSE),
        //'#default_value' => $value['unit'],
        '#prefix' => '<div class="physical-dimensions-unit-form-item">',
        '#suffix' => '</div>',
      );
    
    if(isset($boxes[$i]['unit'])) {
         $form['sizes'][$i]['unit']['#default_value'] = $boxes[$i]['unit'];
       }
   }   
 
  $form['packing_add_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add More'),
    '#prefix' => '<div class="packing-add-more">',
    '#suffix' => '</div>',
    '#submit' => array('commerce_packing_admin_add_more_submit'),
    '#ajax' => array(
      'callback' => 'commerce_packing_admin_add_more',
      'wrapper' => 'boxes-fieldset-wrapper',
    ),
  ); 
 
  $form['packing_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  ); 
   
  drupal_add_library('system', 'drupal.ajax');
  
  return $form;
}

/**
 * Submit handler for admin form.
 */
function commerce_packing_overview_form_submit($form, &$form_state) {
  // Filter out empty rows before saving
  $boxes = array();
 // dsm($form_state['input']['sizes']);
  foreach($form_state['input']['sizes'] AS $i => $size) {
    foreach (physical_dimensions() as $key => $dimension) {
      if(!empty($size[$key])) {
        $boxes[] = $size;
        break;
      }     
    }
  }
  variable_set('commerce_packing_package_sizes', $boxes);
  drupal_set_message(t('Updated package sizes.'));
}

/**
 * Ajax callback
 */
function commerce_packing_admin_add_more($form, &$form_state) {
  return $form['sizes'];
}

/**
 * Add more submit handler
 */
function commerce_packing_admin_add_more_submit($form, &$form_state) {
  $form_state['num_boxes']++;
  $form_state['rebuild'] = TRUE;
}