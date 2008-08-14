////////////////////////////////////////////////////////////////////////////////
///DataWindowInterface.h
///
///Used to add/remove data window used in data acquisition
///
///Author: Ryan Seal
///Modified: 08/06/08
////////////////////////////////////////////////////////////////////////////////
#ifndef DATA_WINDOW_INTERFACE_H
#define DATA_WINDOW_INTERFACE_H

#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Choice.h>
#include <FL/fl_ask.H>
#include "CustomTab.h"
#include "DataGroup.h"
#include "UsrpConfigStruct.h"
#include "DataWindowStruct.h"

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using boost::shared_ptr;

///\todo Add rule checking to DataWindowInterface

///Class definition
class DataWindowInterface : public CustomTab
{
    typedef shared_ptr<DataGroup> DataGroupPtr;
    vector<DataGroupPtr> dataGroupArray_;
    UsrpConfigStruct& usrpConfigStruct_;
    bool defaultWindow_;
    bool arrayTouched_;
    int numWindows_;
    int x0_;
    int y0_;
    int w0_;
    int h0_;

    static void Update(Fl_Widget* flw, void* userData){
	DataGroup* dgPtr = reinterpret_cast<DataGroup*>(flw);

	int id = dgPtr->ID();
	cout << "DataWindowInterface::Update - state change from ID " << id << endl;

	UsrpConfigStruct* ucsPtr = reinterpret_cast<UsrpConfigStruct*>(userData);
	USRP::WindowVector& dws = ucsPtr->WindowRef();

	dws[id].start = dgPtr->Start();
	dws[id].size  = dgPtr->Size();
	dws[id].units = dgPtr->Units();
	
    }
public:
    ///Constructor
    DataWindowInterface(UsrpConfigStruct& usrpConfigStruct, int x, int y,
			int width=325, int height=245, const char* label=NULL);
    void Add(const string& label);
    void Remove(const string label);
    void Modify(const string oldLabel, const string newLabel);
    void Units(const int& units);
};
#endif
