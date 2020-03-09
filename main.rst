
// main.rst
// --- HEADER ------------------------------------------------------------------
// SUMMARY : 
// CREATOR : Jon Dunnett
// EDITS   :
// STATUS  : development  
// -----------------------------------------------------------------------------

// --- USES --------------------------------------------------------------------
use std::error::Error;
use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::env;
// -----------------------------------------------------------------------------

// --- MAIN --------------------------------------------------------------------
fn main () {
  let args: Vec<String> = env.args().collect();
  let iter_limit  = &args[1];
  let in_filename = &args[2];
}