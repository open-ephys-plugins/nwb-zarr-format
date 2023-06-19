/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
//#include <H5Cpp.h>
#include "NWBZarrFileSource.h"
#include <CoreServicesHeader.h>


//using namespace H5;

#define PROCESS_ERROR std::cerr << "NWBFilesource exception: " << error.getCDetailMsg() << std::endl

NWBFileSource::NWBFileSource() : samplePos(0), skipRecordEngineCheck(false)
{
}

NWBFileSource::~NWBFileSource()
{
}

bool NWBFileSource::open(File file)
{

    //Code should never reach here
    return false;
}

void NWBFileSource::fillRecordInfo()
{

    

}

void NWBFileSource::updateActiveRecord(int index)
{

    
}

void NWBFileSource::seekTo(int64 sample)
{
    samplePos = sample % getActiveNumSamples();
}

int NWBFileSource::readData(int16* buffer, int nSamples)
{

   
    return 0;
}

void NWBFileSource::processChannelData(int16* inBuffer, float* outBuffer, int channel, int64 numSamples)
{
    int n = getActiveNumChannels();
    float bitVolts = getChannelInfo(activeRecord.get(), channel).bitVolts;

    for (int i=0; i < numSamples; i++)
    {
        *(outBuffer+i) = *(inBuffer+(n*i)+channel) * bitVolts;
    }

}

void NWBFileSource::processEventData(EventInfo &eventInfo, int64 start, int64 stop)
{

	int local_start = start % getActiveNumSamples();;
	int local_stop = stop % getActiveNumSamples();
	int loop_count = start / getActiveNumSamples();

	EventInfo info = eventInfoMap[currentStream];

	int i = 0;

	while (i < info.timestamps.size())
	{
		if (info.timestamps[i] >= local_start && info.timestamps[i] < local_stop)
		{
			eventInfo.channels.push_back(info.channels[i] - 1);
			eventInfo.channelStates.push_back((info.channelStates[i]));
			eventInfo.timestamps.push_back(info.timestamps[i] + loop_count*getActiveNumSamples());
		}
		i++;
	}

}

bool NWBFileSource::isReady()
{
    /*
	//HDF5 is by default not thread-safe, so we must warn the user.
	if ((!skipRecordEngineCheck) && (CoreServices::getSelectedRecordEngineId() == "NWB"))
	{
		int res = AlertWindow::showYesNoCancelBox(AlertWindow::WarningIcon, "Record format conflict",
			"Both the selected input file for the File Reader and the output file format for recording use the HDF5 library.\n"
			"This library is, by default, not thread safe, so running both at the same time might cause unexpected crashes (chances increase with signal complexity and number of recorded channels).\n\n"
			"If you have a custom-built hdf5 library with the thread safe features turned on, you can safely continue, but performance will be reduced.\n"
			"More information on:\n"
			"https://www.hdfgroup.org/HDF5/doc/TechNotes/ThreadSafeLibrary.html\n"
			"https://www.hdfgroup.org/hdf5-quest.html\n\n"
			"Do you want to continue acquisition?", "Yes", "Yes and don't ask again", "No");
		switch (res)
		{
		case 2:
			skipRecordEngineCheck = true;
		case 1:
			return true;
			break;
		default:
			return false;
		}
	}
	else
		return true;
    */

    return true;
}

