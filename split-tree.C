#include "TFile.h"
#include "TTree.h"
#include <cstdio>

// A macro to split a tree
void usage(const char* name){
  printf("%s /path/to/file.root \n",name);
  printf("Splits tree in file.root in half\n");
  printf("Output files are file.root.0 and file.root.1\n");
  printf("Read the source!\n");
}
void write_tree_hunk(const char* outName, TTree* tree,int i,int n){
  char fileName[2048];
  snprintf(fileName,2048,"%s.%d",outName,i);
  TFile* file=new TFile(fileName,"RECREATE");
  file->cd();
  char cutstring[50];
  snprintf(cutstring,50,"Entry$%%%d==%d",n,i);
  TTree* outTree=tree->CopyTree(cutstring);
  outTree->Write();
  file->Write();
  file->Close();
}
int main(const int argc, const char* argv[]){
  //Exercise for the reader: Add a -t option that takes the name of
  //the tree to be split, put the following in a loop so you can split
  //the file in to n equal parts
  if(argc!=2){
    usage(argv[0]);
    return -1;
  }
  TFile* file=TFile::Open(argv[1]);
  //this shouldn't be hard coded to be useful, but parsing options is
  //a pain in the ass
  TTree* tree=(TTree*)file->Get("micro");
  write_tree_hunk(argv[1],tree,0,2);
  write_tree_hunk(argv[1],tree,1,2);
  /*
  for(int i=0; i < n; i++){
    write_file_hunk(file,i);
  }
  //*/
  return 0;
}
