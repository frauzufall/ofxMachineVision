#pragma once

#include "ofConstants.h"

#ifdef TARGET_OSX

#include "ofxUVC.h"
#include "ofQTKitGrabber.h"

#include "ofxMachineVision/Specification.h"
#include "Updating.h"

namespace ofxMachineVision {
	namespace Device {
		/**
		 \brief Implementation of Greg Borenstein's ofxUVC library as an ofxMachineVision::Device::Updating class
		 */
		class OSXUVCDevice : public Updating {
		public:
			OSXUVCDevice(int width = 640, int height = 480, float desiredFramerate = 30);
			Specification open(int deviceID) override;
			bool startCapture() override;
			void stopCapture() override;
			void close() override;
			void setExposure(Microseconds exposure) override;
			void setGain(float percent) override;
			void setFocus(float percent) override;
			void setSharpness(float percent) override;
			
			void updateIsFrameNew();
			bool isFrameNew();
			shared_ptr<Frame> getFrame();
			
			//--
			void resetTimestamp();
		protected:
			ofQTKitGrabber device;
			ofxUVC controller;
			
			int deviceID;
			int width, height;
			float desiredFramerate;
			
			uint64_t timerStart;
			long frameIndex;
			
			shared_ptr<Frame> frame;
		};
		
		typedef OSXUVCDevice Webcam;
	}
}

#endif