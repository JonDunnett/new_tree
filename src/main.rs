// main.rst
// --- HEADER ------------------------------------------------------------------
// SUMMARY : 
// CREATOR : Jon Dunnett
// EDITS   :
// STATUS  : figure out how to output file 
// -----------------------------------------------------------------------------

// --- EXTERN ------------------------------------------------------------------
extern crate json;
// -----------------------------------------------------------------------------

// --- USES --------------------------------------------------------------------
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;
use std::env;
use json::*;
// -----------------------------------------------------------------------------

// --- MAIN --------------------------------------------------------------------
fn main () {
  let args: Vec<String> = env::args().collect();
  let iter_limit  = &args[1];
  let in_filename = &args[2];
  


  let grammar = 
    read_grammar(in_filename.to_string())
      .expect("failed to open json") ;

  let _iter_limit = 
    iter_limit.parse::<i32>().unwrap() ;
  for i in 0.._iter_limit {
    println!("iter {}", i);
  }

  let f = File::open("");

}

// --- HELPER FUNCTIONS --------------------------------------------------------
// just some functions to help out a little bit 

fn read_grammar (infile_name : String) 
  -> std::result::Result<json::JsonValue, json::Error>  {
// input filename as json with defined grammar 
// PRE : existing string filename with relative file path 
// POST: returns a json as a grammar 
  // try to open file 
  let file = File::open(infile_name);

  match file.is_ok() {
    true  =>  true,
    false =>  panic!("Error loading file")
  };

  let mut idk = file.unwrap();

  // load into a string
  let mut contents = String::new();
  idk.read_to_string(&mut contents);
  return json::parse(&mut contents);
}

fn read_bytes(
  infile_name : String,
  outfile_name : String,
  grammar : json::JsonValue 
) {
// reads bytes from input file -- outputs to output file 
// PRE : given string representing the name of an existing file 
// POST: transfers byte by byte infile -> outfile 
  let mut ouf = File::create(outfile_name)
    .expect("Failed to open out file ");
  let inf = File::open(infile_name)
    .expect("Failed to open in file");
  let inf = BufReader::new(inf);
  let mut count = 0;
  let mut output_string = String::new();
  for b in inf.bytes() {
    if b.is_ok() {
      let mut cur_char : String = b.unwrap().to_string();
      if true {
        output_string = grammar.get(cur_char);
      } else {
        output_string = cur_char.to_string();
      }
      // output output string 
      ouf.write_all(output_string.to_string())
        .expect("failed to write to file");
    }
  }
}