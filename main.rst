
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
use std:collections::HashMap;
// -----------------------------------------------------------------------------

// --- MAIN --------------------------------------------------------------------
fn main () {
  let args: Vec<String> = env.args().collect();
  let iter_limit  = &args[1];
  let in_filename = &args[2];

  let mut G = read_grammar(in_filename);
}


// --- HELPER FUNCTIONS --------------------------------------------------------
// just some functions to help out a little bit 

fn read_grammar (infile_name) -> json {
// input filename as json with defined grammar 
// PRE : existing string filename with relative file path 
// POST: returns a json as a grammar 
  let mut file = File::open(infile_name)?;
  let mut contents = String::new();
  file.read_to_string(&mut contents)?;
  return json::parse(&mut contents);
}