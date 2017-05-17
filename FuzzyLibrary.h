/*
	FuzzyLibrary.h 
  
	Created by Amir Zahlan, November, 2014
  
	https://github.com/Amimaro/embFuzzyLibrary.git
  
	Released into the public domain.
*/
 
#ifndef FuzzyLibrary_h
#define FuzzyLibrary_h
#include "Arduino.h"

#define TRI 0
#define REC 1
#define TRA 2
#define GAU 3
 
class Fuzzy  {  
   
  public:
	Fuzzy();    					
	uint8_t createVariable(uint8_t);    	
	uint8_t addTerm(uint8_t);
	void addPointsTo(uint8_t, float, float, float, float);	
	uint8_t createRule(uint8_t, uint8_t, uint8_t, uint8_t);
	uint8_t setVariableValue(uint8_t, float);	
	float getVariableValue(uint8_t);	
	float calculate();		
  private:    
	uint8_t fuzzyVarsCount;
	uint8_t fuzzyTermsCount;
	uint8_t fuzzyPointsCount;	
	uint8_t fuzzyRulesCount;
	uint8_t fuzzyVarsInputCount;
	uint8_t fuzzyVarsOutputCount;		
	uint8_t ** fuzzyTerms;
	uint8_t ** fuzzyRules;
	float ** fuzzyVars;	
	float ** fuzzyPoints;	
	void addPoint(uint8_t, float, uint8_t);
	void swap(int, int);
	void showAllVars();	
	void showAllTerms();
	void showAllPoints();	
	void showAllRules();
};
 
#endif
