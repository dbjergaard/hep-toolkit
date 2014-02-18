// A macro to split a tree
void usage(char* name){
  printf("%s /path/to/file.root\n");
  printf("Splits tree in file.root in half\n");
  printf("Output files are file.root.0 and file.root.1\n");
  printf("Read the source!\n");
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
  char outNameA[1024];
  snprintf(outNameA, 1024, "%s.%d",argv[1],0);
  TTree* tree=(TTree*)file->Get("micro");
  TFile* fileA=new TFile(outnameA,"RECREATE");
  fileA->cd();
  const Long64_t nEntries=tree->GetEntries();
  char cut_strA[25];
  snprintf(cut_strA,25,"Entry$ < %d", nEntries/2);
  TTree* treeA=tree->CopyTree(cut_strA);
  treeA->Write();
  fileA->Write();
  fileA->Close();

  snprintf(outNameA, 1024, "%s.%d",argv[1],1);
  TFile* fileB=new TFile(outNameB,"RECREATE");
  fileB->cd();
  char cut_strB[25];
  snprintf(cut_strB,25,"Entry$ >= %d", nEntries/2);
  TTree* treeB=tree->CopyTree(cut_strB);
  treeB->Write();
  fileB->Write();
  fileB->Close();
  return 0;
}
