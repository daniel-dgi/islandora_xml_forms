<?php

// $Id$

/**
 * @file
 *
 */
module_load_include('inc', 'xml_form_api', 'ActionInterface');
module_load_include('inc', 'xml_form_api', 'Path');

/**
 * 
 */
class Read implements ActionInterface {

  /**
   * Path to the parent element, where the DOMNode will be created.
   * 
   * @var Path
   */
  protected $path;

  /**
   *
   * @param string $xml_definition
   * @return Read
   */
  public static function createFromXMLDefiniton($xml_definition) {
    return self::createFromSimpleXML(simplexml_load_string($xml_definition));
  }

  /**
   *
   * @param SimpleXMLElement $read
   * @return Read
   */
  public static function createFromSimpleXML(SimpleXMLElement $read) {
    $path = (string) $read->path;
    $context = (string) $read->path['context'];
    $params = array(
      'path' => new Path($path, $context),
    );
    return new self($params);
  }

  /**
   * Construct Read Action.
   * 
   * @param array $params
   *   The parameters that initialize this object.
   */
  public function __construct(array &$params) {
    $this->path = $params['path'];
    if (!$this->valid()) {
      throw new Exception('Failed to initialize Read.');
    }
  }

  /**
   * Determine if this object has been initialized correctly.
   * 
   * @return boolean
   *   TRUE if this object is valid FALSE otherwise.
   */
  public function valid() {
    return isset($this->path);
  }

  /**
   *
   * @param NodeRegistry $registry
   * @param FormElement $element
   * @param mixed $value 
   */
  public function execute(NodeRegistry $registry, FormElement $element, $value = NULL) {
    return $this->path->query($registry, $element);
  }

}