/*
	FuzzyLibrary.cpp
  
	Created by Amir Zahlan, November, 2014
  
	https://github.com/Amimaro/embFuzzyLibrary.git
  
	Released into the public domain.
*/

#include "Arduino.h"
#include "FuzzyLibrary.h"

Fuzzy::Fuzzy(){
	fuzzyVarsCount = 0;	
	fuzzyVarsInputCount = 0;
	fuzzyVarsOutputCount = 0;
	fuzzyTermsCount = 0;
	fuzzyPointsCount = 0;	
	fuzzyRulesCount = 0;	
	fuzzyVars = new float * [10];	
	fuzzyTerms = new uint8_t * [30];
	fuzzyPoints = new float * [90];
	fuzzyRules = new uint8_t * [50];
}

uint8_t Fuzzy::createVariable(uint8_t mode){
	if(mode == 0 || mode == 1){	
		fuzzyVars[fuzzyVarsCount] = new float[3];
		fuzzyVars[fuzzyVarsCount][0] = mode;				
		fuzzyVars[fuzzyVarsCount][1] = 0.0f;
		fuzzyVars[fuzzyVarsCount][2] = 0.0f;
		fuzzyVarsCount++;
		return fuzzyVarsCount-1;
	} else {		
		return NULL;
	}	
}

uint8_t Fuzzy::setVariableValue(uint8_t var, float input){
	if(!fuzzyVars[var][0]){
		fuzzyVars[var][1] = input;		
		return 1;
	} else {		
		return 0;
	}	
}

float Fuzzy::getVariableValue(uint8_t var){
	return fuzzyVars[var][1];;
}

uint8_t Fuzzy::addTermTo(uint8_t fuzzyVar, uint8_t type){
	if(fuzzyVar >= 0 || fuzzyVar < fuzzyVarsCount){				
		fuzzyTerms[fuzzyTermsCount] = new uint8_t [2];
		fuzzyTerms[fuzzyTermsCount][0] = fuzzyVar;		
		fuzzyTerms[fuzzyTermsCount][1] = type;		
		fuzzyTermsCount++;
		return fuzzyTermsCount-1;
	} else {		
		return NULL;
	}
}

void Fuzzy::addPoint(uint8_t fuzzyTerm, float q, uint8_t w){
	fuzzyPoints[fuzzyPointsCount] = new float [3];
	fuzzyPoints[fuzzyPointsCount][0] = fuzzyTerm;			
	fuzzyPoints[fuzzyPointsCount][1] = q;
	fuzzyPoints[fuzzyPointsCount][2] = w;		
	fuzzyPointsCount++;
}

void Fuzzy::addPointsTo(uint8_t fuzzyTerm, float a, float b, float c, float d){			
	if(fuzzyTerm >= 0 || fuzzyTerm < fuzzyTermsCount){		
		addPoint(fuzzyTerm, a, 0);
		addPoint(fuzzyTerm, b, 1);
		addPoint(fuzzyTerm, c, 1);
		addPoint(fuzzyTerm, d, 0);						
	}
}

uint8_t Fuzzy::createRule(uint8_t conditionVar, uint8_t conditionTerm, uint8_t conclusionVar, uint8_t conclusionTerm){
	if((conditionTerm >= 0 || conditionTerm < fuzzyRulesCount) && (conclusionTerm >= 0 || conclusionTerm < fuzzyRulesCount)){
		fuzzyRules[fuzzyRulesCount] = new uint8_t [4];
		fuzzyRules[fuzzyRulesCount][0] = conditionVar;
		fuzzyRules[fuzzyRulesCount][1] = conditionTerm;
		fuzzyRules[fuzzyRulesCount][2] = conclusionVar;
		fuzzyRules[fuzzyRulesCount][3] = conclusionTerm;
		fuzzyRulesCount++;
		return fuzzyRulesCount-1;
	} else {		
		return NULL;
	}	
}

float Fuzzy::calculate(){
	
	double centroid = 0.0f, tmpCentroid = 0.0f;	
	uint8_t f = 0;
	
	for(uint8_t i = 0; i < fuzzyRulesCount; i++){
		if(!fuzzyVars[fuzzyRules[i][0]][0]){
			float input = fuzzyVars[fuzzyRules[i][0]][1], output = 0.0f, pertIn[4], pertOut[4];			
			int q = 0, q2 = 0;			
			
			for(int j = 0; j < fuzzyPointsCount; j++){								
				if(fuzzyPoints[j][0] == fuzzyRules[i][1]){					
					pertIn[q] = fuzzyPoints[j][1];					
					q++;					
				}
				if(fuzzyPoints[j][0] == fuzzyRules[i][3]){					
					pertOut[q2] = fuzzyPoints[j][1];					
					q2++;					
				}
			}			
			float a = pertIn[0], b = pertIn[1], c = pertIn[2], d = pertIn[3];
			float a2 = pertOut[0], b2 = pertOut[1], c2 = pertOut[2], d2 = pertOut[3];	
									
			if(input < a){				
				output = 0.0f;
			} else if(input > d){				
				output = 0.0f;
			} else if(a == b && b == c && c == d && d == a){		
				output = 1.0f;
			} else if((a == b || a == c) && (d == b || d == c) && (c != b || b != c)){
				output = 1.0f;
			} else if(a < b && a < c && b == c && c == d){
				if(input == a){					
					output = 0.0f;
				} else {					
					output = (input - a)/(b - a);
				}
			} else if(d > b && d > c && a == b && b == c){
				if(input == d){					
					output = 0.0f;
				} else { 					
					output = (d - input)/(d - c);
				}
			} else if(a < b && a < c && b == c && d > b && d > c){
				if(input > a && input <= b){					
					output = (input - a)/(b - a);
				} else if(input > c && input <= d){					
					output = (d - input)/(d - c);
				}
			} else {
				if(input > a && input <= b){					
					output = (input - a)/(b - a);
				} else if(input >= b && input <= c){					
					output = 1.0f;
				} else if(input > c && input <= d){					
					output = (d - input)/(d - c);
				}
			}				
			
			tmpCentroid = 0.0f;
			
			for(int m = a2; m <= d2; m++){
				tmpCentroid+=m;
			}
			
			tmpCentroid = (tmpCentroid * output)/(d2-a2); 			
			centroid += tmpCentroid;
			if(output > 0.0f) f++;
		}		
	}
	if(f == 0)
		return 0.0f;
	else
		return centroid/f;
}

/***********************************Print Functions/************************************/

void Fuzzy::showAllVars(){	
	for(int i = 0; i < fuzzyVarsCount; i++){
		for(int j = 0; j < 2; j++){
			Serial.print(fuzzyVars[i][j]);
			Serial.print(" ");
		}
		Serial.println(" ");
	}	
}

void Fuzzy::showAllTerms(){
	for(int i = 0; i < fuzzyTermsCount; i++){
		for(int j = 0; j < 2; j++){
			Serial.print(fuzzyTerms[i][j]);
			Serial.print(" ");
		}
		Serial.println(" ");
	}
}

void Fuzzy::showAllPoints(){
	for(int i = 0; i < fuzzyPointsCount; i++){
		for(int j = 0; j < 3; j++){
			Serial.print(fuzzyPoints[i][j]);
			Serial.print(" ");
		}
		Serial.println(" ");
	}
}

void Fuzzy::showAllRules(){
	for(int i = 0; i < fuzzyRulesCount; i++){
		for(int j = 0; j < 4; j++){
			Serial.print(fuzzyRules[i][j]);
			Serial.print(" ");
		}
		Serial.println(" ");
	}
}
