#include "sentence_reader.hpp"
#include "histogram.hpp"
#include "lower_case.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <cmath>

struct out_param {
  string oword;
  double os_tw;
  int oa_w;
  int oc_tw;

  //bool operator() (out_param i, out_param j) {return (i.os_tw > j.os_tw);}
};

int main (int argc, char **argv) {

  string target = argv[1];
  cerr << "Target taken" << endl;

  vector<pair<string,int>> close_counts; //words in the same sentence at the target word.
  vector<pair<string,int>> all_counts; //same words as close_counts, but also counting in sentences without target word.

  bool tfound;

  while(1) {
    SentenceReader eater(cin);

    vector<string> sentence = eater.next();
    cerr << "Sentence Reader created and reading next sentence." << endl;

   if (sentence.empty()) {
	    break;
   }

    for (int i=0; i<sentence.size(); i++) {
      if (i!= sentence.size()-1) {
        cerr << sentence[i] << " ";
      } else {
        cerr << sentence[i] << endl;
      }
    }

    //identify close sentences
    tfound = false;
    for (int i=0; i<sentence.size(); i++) {
      if (sentence[i] == target) {
        cerr << "found target in word" << i << endl;
        tfound = true;
        break;
      }
    }

    //starts counting: upper part is for closed sentences; lower part for non-closed sentences.
    if (tfound) {
      cerr << "sentence size is " << sentence.size() << endl;
      for (int j=0; j<sentence.size(); j++) { //for close sentences
        if (sentence[j] != target) {
          cerr << "adding close and all count for close word" << j << endl;
          histogram_add(close_counts , sentence[j]);
          histogram_add(all_counts, sentence[j]);
        }
      }
    } else { //for non-closed sentences.
      cerr << "sentence size is " << sentence.size() << endl;
      for (int j=0; j<sentence.size(); j++) {
        //assert(sentence[j] != target);
        cerr << "adding all count for non-closed sentence, word" << j << endl;
        histogram_add(all_counts , sentence[j]);
        cerr << "done adding" << endl;
      }
    }

    /*
    for (int i=0; i<sentence.size();i++) {
      histogram_add(all_counts , sentence[i]);
      if (tfound && (sentence[i] !=target)) {
        histogram_add(close_counts , sentence[i]);
      }
    }
    */
}


//Calculating output parameters.
cerr << "calculating output parameters." << endl;
vector<out_param> output;
for (int i=0; i<all_counts.size(); i++) {   //initialising values

  bool close = false;
  //string w = all_counts[i].first; //all_word
  //int a_w = all_counts[i].second; //all_count
  int c_tw = 0;
  cerr << "initialised parameters" << endl;

  for (int j=0; j<close_counts.size(); j++) { //collecting all_count data for close_count words.
    if (close_counts[j].first == all_counts[i].first) {
      c_tw = close_counts[j].second;
      cerr << "close word matched to all counts" <<  " " << close_counts[j].first << endl;
      close = true;
      break;
    }
  }

  if (close == true) {

    out_param o_word;
    o_word.oword = all_counts[i].first; //w;

    o_word.oa_w = all_counts[i].second; //a_w;
    o_word.oc_tw = c_tw;

    double s_tw = c_tw/ sqrt(o_word.oa_w);
    o_word.os_tw = s_tw;

    output.push_back(o_word);
    cerr << "pushed back the word " << " " << o_word.oword << endl;
  }

}

cerr << "currently words added to output, not ordered, are" << endl;
for (int i=0; i<20; i++) {
  cout << output[i].oword << " ";
  if (i==19) {cout << endl;}
}

//sort the vector of output_params (output)
sort(output.begin(), output.end(),
  [] (const out_param &left, const out_param &right)
      {
        if (left.os_tw == right.os_tw)
          return (left.oword < right.oword);
        else
          return (left.os_tw> right.os_tw);
      }
    );

//print everything.
for (int i=0; i<10; i++) {
  cout << output[i].oword << " " << output[i].os_tw << " " ;
  cout << output[i].oa_w << " "  << output[i].oc_tw << endl;
}

}
