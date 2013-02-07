{
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TNtupleD.h>
#include <TLegend.h>

	gROOT->Reset();
	gStyle->SetCanvasColor(33);
	gStyle->SetFrameFillColor(18);
	
	Double_t event,energy,posx,posy,posz,p_event;
	p_event=1001;

	TH1D* h1 = new TH1D("H1","Events",1000,0,1010);
	TH1D* h2 = new TH1D("H2","Emission Spectrum", 1000, 200,800); 

	TFile* file = new TFile("LYSO.root");
	TNtupleD* ntuple1 = (TNtupleD*)gROOT->FindObject("Tuple");

	ntuple1->SetBranchAddress("event",&event);
	ntuple1->SetBranchAddress("energy",&energy);
	ntuple1->SetBranchAddress("pos_x",&posx);
	ntuple1->SetBranchAddress("pos_y",&posy);
	ntuple1->SetBranchAddress("pos_z",&posz);

	for(Int_t i=0; i<ntuple1->GetEntries();i++){
		ntuple1->GetEntry(i);
		if(energy != 0)	{
			h1->Fill(event);
			h2->Fill(energy);
		}
		if(event!=p_event){
			cout<<"Event: "<<event<<endl;
			p_event=event;
		}
	}
	h1->SetLineColor(kRed);
	h1->SetStats(false);

/*	TH1D* h2 = new TH1D("H2","Emission Spectrum",600,200,800);

	TFile* file = new TFile("LYSO100PFP.root");
	TNtupleD* ntuple2 = (TNtupleD*)gROOT->FindObject("Tuple");

	ntuple2->SetBranchAddress("event",&event);
	ntuple2->SetBranchAddress("energy",&energy);
	ntuple2->SetBranchAddress("pos_x",&posx);
	ntuple2->SetBranchAddress("pos_y",&posy);
	ntuple2->SetBranchAddress("pos_z",&posz);

	for(Int_t i=0; i<ntuple2->GetEntries();i++){
		ntuple2->GetEntry(i);
		if(energy != 0)	h2->Fill(energy);
	}
	h2->SetLineColor(kGreen);
	h2->SetStats(false);

	TH1D* h3 = new TH1D("H3","Emission Spectrum",600,200,800);

	TFile* file = new TFile("LYSO100PBP.root");
	TNtupleD* ntuple3 = (TNtupleD*)gROOT->FindObject("Tuple");

	ntuple3->SetBranchAddress("event",&event);
	ntuple3->SetBranchAddress("energy",&energy);
	ntuple3->SetBranchAddress("pos_x",&posx);
	ntuple3->SetBranchAddress("pos_y",&posy);
	ntuple3->SetBranchAddress("pos_z",&posz);

	for(Int_t i=0; i<ntuple3->GetEntries();i++){
		ntuple3->GetEntry(i);
		if(energy != 0) h3->Fill(energy);
	}
	h3->SetLineColor(kBlue);
	h3->SetStats(false);*/

TCanvas* c1 = new TCanvas("C1","Canvas");
c1->SetGrid();
//c1->Divide(1,2);

h1->GetXaxis()->SetNdivisions(530, 1);
h1->GetXaxis()->SetTitle("Number Of Event");
h1->GetYaxis()->SetTitle("Counts");
h2->GetXaxis()->SetTitle("Wavelenght[nm]");
h2->GetYaxis()->SetTitle("Counts");
//c1->cd(1);
//h1->Draw();
//c1->cd(2);
h2->Draw();
//h2->Draw("same");
//h3->Draw("same");

/*TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
   legend->AddEntry(h1,"Polished","l");
   legend->AddEntry(h2,"Polished Front Painted","l");
   legend->AddEntry(h3,"Polished Back Painted","l");
   legend->Draw();*/
}
