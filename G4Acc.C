#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "TFile.h"
#include "TKey.h"
#include "TTree.h"
#include "TChain.h"
#include "TEntryList.h"

#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"

#include "./include/THypHi_UTrackerHit.hh"
#include "./include/THypHi_Event.hh"

#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

void G4Acc(const std::string& name_in)
{
  TFile* input_file = new TFile(name_in.c_str());

  TTree* InTree = 0;
  InTree = dynamic_cast<TTree*> (input_file->Get("G4Tree"));
  assert(InTree!=0);

  THypHi_Event* fEvent = 0;
  InTree->SetBranchAddress("THypHi_Event", &fEvent);
   
 
  std::vector<std::string> nameDet= {"TR0","TR1","DC1","TR2","DC2","DC3","DC2STOP"};
  
  std::unordered_map<std::string, TClonesArray*> AllHits;
  for(auto name : nameDet)
    {
      auto it = AllHits.insert(std::make_pair(name, new TClonesArray("UTrackerHit",20)));
      
      InTree->SetBranchAddress(name.c_str(),&(it.first->second));
      it.first->second->SetName(name.c_str());
    }


  // for(auto name : nameDet)
  //   AllHits.insert(std::make_pair(name,new TTreeReaderArray<UTrackerHit>(reader,name.c_str())));


  std::vector< std::vector<TH1F*> > AllAcc (4);
  AllAcc[0].emplace_back(new TH1F("TR2_d1_x","TR2_d1_x",600/6,-60,60));
  AllAcc[0].emplace_back(new TH1F("DC2_d1_x","DC2_d1_x",600/6,-100,150));
  AllAcc[0].emplace_back(new TH1F("DC3_d1_x","DC3_d1_x",600/6,0,300));
  AllAcc[1].emplace_back(new TH1F("TR2_d2_x","TR2_d2_x",600/6,-60,60));
  AllAcc[1].emplace_back(new TH1F("DC2_d2_x","DC2_d2_x",600/6,-100,150));
  AllAcc[1].emplace_back(new TH1F("DC3_d2_x","DC3_d2_x",600/6,0,300));

  AllAcc[2].emplace_back(new TH1F("TR2_d1_xAll","TR2_d1_xAll",600/6,-60,60));
  AllAcc[2].emplace_back(new TH1F("DC2_d1_xAll","DC2_d1_xAll",600/6,-100,150));
  AllAcc[2].emplace_back(new TH1F("DC3_d1_xAll","DC3_d1_xAll",600/6,0,300));
  AllAcc[3].emplace_back(new TH1F("TR2_d2_xAll","TR2_d2_xAll",600/6,-60,60));
  AllAcc[3].emplace_back(new TH1F("DC2_d2_xAll","DC2_d2_xAll",600/6,-100,150));
  AllAcc[3].emplace_back(new TH1F("DC3_d2_xAll","DC3_d2_xAll",600/6,0,300));


  
  TH1F* PosAtDC3 = new TH1F("PosAtDC3","PosAtDC3",300,0,300);
  TH2F* Acceptance = new TH2F("Acc","Acc",20,0,20,20,0,20);
  TH2F* BrhoBrho = new TH2F("BrhoBrho","BrhoBrho",200,10,20,200,0,4);
  TH2F* BrhoBrho2 = new TH2F("BrhoBrhoDC3","BrhoBrhoDC3",200,10,20,200,0,4);
  Long64_t Start_event=0;
  Long64_t Stop_event=InTree->GetEntries();
  int timing = 0;

  for(Long64_t i = Start_event;i<Stop_event;++i)
    {
      if(static_cast<int>(static_cast<double>(i)/static_cast<double>(Stop_event)*10)==timing)
	{
	  std::cout<<"Processing :"<<timing*10<<"% \n";
	  ++timing;
	}
      InTree->GetEntry(i);
      
      
      std::string nameMother (fEvent->MotherName);
      int id_mother = fEvent->MotherTrackID;

      std::vector<int> id_daugthers (2);//fEvent->DaughterTrackID.size());
      std::vector<int> charge_daugthers(2);//fEvent->DaughterTrackID.size());
      std::vector<TLorentzVector> P_daugthers(2);//fEvent->DaughterTrackID.size());
      std::vector<TLorentzVector> Pos_daugthers(2);//fEvent->DaughterTrackID.size());
      std::vector<std::string> nameD(2);

      for(size_t index = 0,id_D=0; index < fEvent->DaughterTrackID.size();++index)
	{
	  
	  assert(id_mother==fEvent->MotherTrackID);
	  if(fEvent->DaughterCharges[index]==0)
	    continue;
	  nameD[id_D]=fEvent->DaughterNames[index];
	  id_daugthers[id_D]=fEvent->DaughterTrackID[index];
	  charge_daugthers[id_D]=fEvent->DaughterCharges[index];
	  P_daugthers[id_D].SetXYZM(fEvent->DaughterMomentums_X[index],fEvent->DaughterMomentums_Y[index],fEvent->DaughterMomentums_Z[index],fEvent->DaughterMasses[index]);
	  Pos_daugthers[id_D].SetXYZT(fEvent->DecayVertex_X,fEvent->DecayVertex_Y,fEvent->DecayVertex_Z,fEvent->DecayTime);
	  ++id_D;
	}

      bool DC2_detected[2] = {false,false};

      auto DC2_branch = AllHits.find("DC2");
      auto TR2_branch = AllHits.find("TR2");
      auto DC3_branch = AllHits.find("DC3");
      if(DC2_branch!=AllHits.end())
	{
	  
	  for(int j=0;j<DC2_branch->second->GetEntries();++j)
	    {
	      UTrackerHit* hit = dynamic_cast<UTrackerHit*>(DC2_branch->second->At(j));
	      for(size_t index_d = 0;index_d<id_daugthers.size();++index_d)
		if(hit->TrackID==id_daugthers[index_d])
		  {
		    AllAcc[index_d+2][1]->Fill(hit->HitPosX);			
		    DC2_detected[index_d]=true;
		    //std::string tempName("DC2");
		    //tempName+=nameD[index_d];
		    Acceptance->Fill("DC2",nameD[index_d].c_str(),1.);
		    
		  }
	    }
	}
      if(TR2_branch!=AllHits.end())
	{
	  
	  for(int j=0;j<TR2_branch->second->GetEntries();++j)
	    {
	      UTrackerHit* hit = dynamic_cast<UTrackerHit*>(TR2_branch->second->At(j));
	      for(size_t index_d = 0;index_d<id_daugthers.size();++index_d)
		if(hit->TrackID==id_daugthers[index_d])
		  {
		    AllAcc[index_d+2][0]->Fill(hit->HitPosX);			
		    Acceptance->Fill("TR2",nameD[index_d].c_str(),1.);
		  }
	    }
	}
      if(DC3_branch!=AllHits.end())
	{
	  
	  for(int j=0;j<DC3_branch->second->GetEntries();++j)
	    {
	      UTrackerHit* hit = dynamic_cast<UTrackerHit*>(DC3_branch->second->At(j));
	      for(size_t index_d = 0;index_d<id_daugthers.size();++index_d)
		if(hit->TrackID==id_daugthers[index_d])
		  {
		    AllAcc[index_d+2][2]->Fill(hit->HitPosX);			
		    Acceptance->Fill("DC3",nameD[index_d].c_str(),1.);
		  }
	    }
	}

      double brho[2] = {0.,0.};
	  
      if(DC2_detected[0] && DC2_detected[1])
	{
	  if(TR2_branch!=AllHits.end())
	    {

	      for(int j=0;j<TR2_branch->second->GetEntries();++j)
		{
		  UTrackerHit* hit = dynamic_cast<UTrackerHit*>(TR2_branch->second->At(j));
		  for(size_t index_d = 0;index_d<id_daugthers.size();++index_d)
		    if(hit->TrackID==id_daugthers[index_d])
		      {
			AllAcc[index_d][0]->Fill(hit->HitPosX);			
			Acceptance->Fill("TR2Coin",nameD[index_d].c_str(),1.);
			brho[index_d] = 3.10715497*TMath::Sqrt(hit->MomX*hit->MomX+hit->MomY*hit->MomY+hit->MomZ*hit->MomZ)/charge_daugthers[index_d];
		      }
		}
	      if(brho[0]<0)
		BrhoBrho->Fill(brho[1],-brho[0]);
	      else if(brho[1]<0)
		BrhoBrho->Fill(brho[0],-brho[1]);
	      
	    }
	  if(DC2_branch!=AllHits.end())
	    {
	      for(int j=0;j<DC2_branch->second->GetEntries();++j)
		{
		  UTrackerHit* hit = dynamic_cast<UTrackerHit*>(DC2_branch->second->At(j));
		  for(size_t index_d = 0;index_d<id_daugthers.size();++index_d)
		    if(hit->TrackID==id_daugthers[index_d])
		      {
			AllAcc[index_d][1]->Fill(hit->HitPosX);
			Acceptance->Fill("DC2Coin",nameD[index_d].c_str(),1.);
			if(charge_daugthers[index_d]==-1)
			  {
			    PosAtDC3->Fill(hit->MomX/hit->MomZ*200.);
			  }
		      }
		}
	      if(DC3_branch!=AllHits.end())
		{
		  for(int j=0;j<DC3_branch->second->GetEntries();++j)
		    {
		      UTrackerHit* hit = dynamic_cast<UTrackerHit*>(DC3_branch->second->At(j));
		      for(size_t index_d = 0;index_d<id_daugthers.size();++index_d)
			if(hit->TrackID==id_daugthers[index_d])
			  {
			    AllAcc[index_d][2]->Fill(hit->HitPosX);
			    Acceptance->Fill("DC3",nameD[index_d].c_str(),1.);

			    double temp_brho = 3.10715497*TMath::Sqrt(hit->MomX*hit->MomX+hit->MomY*hit->MomY+hit->MomZ*hit->MomZ)/charge_daugthers[index_d];
			    if(temp_brho<0)
			      {
				if(brho[0]>0)
				  BrhoBrho2->Fill(brho[0],-temp_brho);
				else if(brho[1]>0)
				  BrhoBrho2->Fill(brho[1],-temp_brho);
			      }
			  }
		  
		    }
		}
	    }
	}
    }

  auto DoEff = [] (TH1F* h1, TH1F* hall) -> TH1F* {

		 std::string nameAcc(h1->GetName());
		 nameAcc+="GeoAcceptance";
		 for(int n = 1; n<=h1->GetNbinsX();++n)
		   {
		     Int_t Nall = hall->GetBinContent(n);
		     Int_t Nacc = h1->GetBinContent(n);
		     if(Nall<=0)
		       {
			 Nacc=0;
			 h1->SetBinContent(n,Nacc);
		       }
		     if(Nall<Nacc)
		       {
			 Nacc = Nall;
			 h1->SetBinContent(n,Nacc);
		       }
		   }
		 
		 if(h1->GetEntries()>1)
		   {
		     TH1F* htmp = (TH1F*) h1->Clone();
		     htmp->GetXaxis()->SetRangeUser(hall->GetXaxis()->GetXmin(),hall->GetXaxis()->GetXmax());
		     htmp->Sumw2();
		     hall->Sumw2();
		     htmp->SetNameTitle(nameAcc.c_str(),nameAcc.c_str());
		     htmp->Divide(hall);
		     return htmp;
		   }
		 else
		   return nullptr;
	       };

  



  
  TFile* f_out = new TFile("f_out.root","RECREATE");
  f_out->cd();

  for(size_t i = 0; i<AllAcc.size();++i)
    for(size_t j = 0; j<AllAcc[i].size();++j)
      AllAcc[i][j]->Write();
  // AllAcc[0][1]->Write();
  // AllAcc[0][2]->Write();
  // AllAcc[1][0]->Write();
  // AllAcc[1][1]->Write();
  // AllAcc[1][2]->Write();

  for(size_t i = 0; i<AllAcc.size()/2;++i)
    for(size_t j = 0; j<AllAcc[i].size();++j)
      {
	TH1F* Htemp = DoEff(AllAcc[i][j],AllAcc[i+2][j]);
	if(Htemp!=nullptr)
	  Htemp->Write();
      }

  BrhoBrho->Write();
  BrhoBrho2->Write();
  PosAtDC3->Write();
  Acceptance->Write();
  f_out->Close();

}
