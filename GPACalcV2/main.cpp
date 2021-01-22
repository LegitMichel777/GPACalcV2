//
//  GPACalcV2
//
//  Created by LegitMichel777
//  Copyright © 2020 LegitMichel777. All rights reserved.
//

#include <iostream>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
struct levelcmp{
    bool operator()(const string &a,const string &b)const {
        map<string,ll>sclvl;
        sclvl["ib"]=1;
        sclvl["ap"]=2;
        sclvl["h+"]=3;
        sclvl["h"]=4;
        sclvl["s+"]=5;
        sclvl["s"]=6;
        sclvl["adv+"]=7;
        sclvl["adv"]=8;
        sclvl["high"]=9;
        sclvl["mid+"]=10;
        sclvl["mid"]=11;
        sclvl["low"]=12;
        sclvl["entry"]=13;
        return sclvl[a]<sclvl[b];
    }
};
struct subj {
    double v;
    map<string,double,levelcmp>level;
};
struct latentcalc {
    string lvl;
    ll sc;
};
struct analy {
    string subj;
    double impt;
    ll subjc;
};
double scale(double x) {
    if (x<0) return 0;
    else if (x<60) return 0;
    else if (x<68) return 2.6;
    else if (x<73) return 3.0;
    else if (x<78) return 3.3;
    else if (x<83) return 3.6;
    else if (x<88) return 3.9;
    else if (x<93) return 4.2;
    else if (x<=100) return 4.5;
    return 0;
}
bool cmp(analy const &a,analy const &b) {
    if (a.impt>b.impt) return true;
    else if (a.impt<b.impt) return false;
    else return a.subj<b.subj;
}
int main() {
    map<string,subj>subject_configuration;
    //TODO:Add subject overwrite
    
    
    /* -----CONFIGURE SUBJECTS----- */
    //IMPORTANT:Set all to lowercase
    //CONFIGURE SUBJECT LEVEL GPA OFFSETS HERE
    map<string,double,levelcmp>non_language_subject_offset;
    non_language_subject_offset["ib"]=non_language_subject_offset["ap"]=0;
    non_language_subject_offset["h"]=-0.2;
    non_language_subject_offset["s+"]=-0.35;
    non_language_subject_offset["s"]=-0.5;
    map<string,double,levelcmp>chinese_subject_offset;
    chinese_subject_offset["ib"]=0;
    chinese_subject_offset["h+"]=-0.1;
    chinese_subject_offset["h"]=-0.2;
    chinese_subject_offset["ap"]=chinese_subject_offset["s"]=chinese_subject_offset["adv+"]=chinese_subject_offset["adv"]=chinese_subject_offset["high"]=-0.3;
    chinese_subject_offset["mid+"]=chinese_subject_offset["mid"]=-0.4;
    chinese_subject_offset["low"]=chinese_subject_offset["entry"]=-0.5;
    map<string,double,levelcmp>english_subject_offset;
    english_subject_offset["ib"]=english_subject_offset["ap"]=0;
    english_subject_offset["h+"]=-0.1;
    english_subject_offset["h"]=-0.2;
    english_subject_offset["s+"]=-0.4;
    english_subject_offset["s"]=-0.5;
    //CONFIGURE SUBJECT WEIGHTS HERE
    subject_configuration["math"]=(subj){5.5,non_language_subject_offset};
    subject_configuration["english"]=(subj){5.5,english_subject_offset};
    subject_configuration["history"]=(subj){4,non_language_subject_offset};
    subject_configuration["chinese"]=(subj){3,chinese_subject_offset};
    subject_configuration["elective"]=(subj){3,non_language_subject_offset};
    subject_configuration["apecon"]=(subj){4,non_language_subject_offset};
    subject_configuration["chemistry"]=(subj){3,non_language_subject_offset};
    subject_configuration["physics"]=(subj){3,non_language_subject_offset};
    subject_configuration["aphist"]=(subj){5,non_language_subject_offset};

    //CONFIGURE SUBJECT ALTERNATIVE NAMES HERE
    multimap<string,string>subjectshortcuts;
    subjectshortcuts.insert(pair<string,string>("eng","english"));
    subjectshortcuts.insert(pair<string,string>("hist","history"));
    subjectshortcuts.insert(pair<string,string>("elec","elective"));
    subjectshortcuts.insert(pair<string,string>("it","elective"));
    subjectshortcuts.insert(pair<string,string>("bio","elective"));
    subjectshortcuts.insert(pair<string,string>("geo","elective"));
    subjectshortcuts.insert(pair<string,string>("econ","elective"));
    subjectshortcuts.insert(pair<string,string>("chi","chinese"));
    subjectshortcuts.insert(pair<string,string>("chem","chemistry"));
    subjectshortcuts.insert(pair<string,string>("phys","physics"));
    /* -----CONFIGURE SUBJECTS----- */
    multimap<string,string>staaka;
    for (multimap<string,string>::iterator it=subjectshortcuts.begin();it!=subjectshortcuts.end();it++) staaka.insert(pair<string,string>(it->second,it->first));
    cout<<"GPA Calculator v3.1 by LegitMichel777. Built for 10th graders of year 2020-2021."<<endl<<"Subjects:"<<endl;
    for (map<string,subj>::iterator i=subject_configuration.begin();i!=subject_configuration.end();i++) {
        string toout=i->first;
        toout[0]=toupper(toout[0]);
        cout<<toout;
        multimap<string,string>::iterator pt;
        if ((pt=staaka.find(i->first))!=staaka.end()) {
            cout<<"("<<(pt++->second);
            if (pt!=staaka.end()) while (pt->first==i->first) cout<<","<<(pt++)->second;
            cout<<")";
        }
        cout<<":";
        map<string,double>::iterator j=i->second.level.begin();
        toout=j++->first;
        transform(toout.begin(),toout.end(),toout.begin(),::toupper);
        cout<<toout;
        for (;j!=i->second.level.end();j++) {
            toout=j->first;
            transform(toout.begin(),toout.end(),toout.begin(),::toupper);
            cout<<"/"<<toout;
        }
        cout<<endl;
    }
    cout<<"Enter subject followed by level and score. Seperate them with spaces. Example line: eng h+ 100. Press return after each line and press return twice when you're finished."<<endl;
    map<string,latentcalc>sctd;
    while (true) {
        string usrin;
        getline(cin,usrin);
        if (usrin=="") break;
        transform(usrin.begin(),usrin.end(),usrin.begin(),::tolower);
        subj subjinf;
        if (usrin.find(' ')!=string::npos) {
            string sujn=usrin.substr(0,usrin.find(' '));
            usrin.erase(0,usrin.find(' ')+1);
            if (subjectshortcuts.find(sujn)!=subjectshortcuts.end()) sujn=subjectshortcuts.find(sujn)->second;
            if (subject_configuration.find(sujn)!=subject_configuration.end()) {
                if (usrin.find(' ')!=string::npos) {
                    string sujl=usrin.substr(0,usrin.find(' '));
                    if (subject_configuration[sujn].level.find(sujl)!=subject_configuration[sujn].level.end()) {
                        usrin.erase(0,usrin.find(' ')+1);
                        ll sujc=atoll(usrin.c_str());
                        sctd[sujn]=(latentcalc){sujl,sujc};
                    } else cout<<"Level doesn't exist!"<<endl;
                } else cout<<"Error in input! Syntax:[SUBJECT] [LEVEL] [SCORE]"<<endl;
            } else cout<<"Subject doesn't exist!"<<endl;
        } else cout<<"Error in input! Syntax:[SUBJECT] [LEVEL] [SCORE]"<<endl;
    }
    double gpa=0,pt=0,maxval=0,minval=1e6;
    for (map<string,latentcalc>::iterator it=sctd.begin();it!=sctd.end();it++) {
        pt+=subject_configuration[it->first].v;
        double impact=subject_configuration[it->first].v*(scale(it->second.sc)+subject_configuration[it->first].level[it->second.lvl]);
        if (it->second.sc>=60) gpa+=impact;
    }
    analy insight[sctd.size()];
    ll tot=0;
    gpa/=pt;
    for (map<string,latentcalc>::iterator it=sctd.begin();it!=sctd.end();it++) {
        double impact=subject_configuration[it->first].v*(scale(it->second.sc)+subject_configuration[it->first].level[it->second.lvl]);
        string beautify=it->first;
        beautify[0]=toupper(beautify[0]);
        insight[tot++]=(analy){beautify,impact,it->second.sc};
        maxval=max(maxval,impact);
        minval=min(minval,impact);
    }
    double nml=max(maxval,-minval);
    sort(insight,insight+tot,cmp);
    cout<<"Your GPA is "<<fixed<<setprecision(3)<<gpa<<endl<<"Subject impacts:"<<endl;
    for (ll i=0;i<sctd.size();i++) cout<<insight[i].subj<<"("<<insight[i].subjc<<"):"<<insight[i].impt/nml<<endl;
    cout<<"Press return to exit...";
    cin.get();
    return 0;
}
