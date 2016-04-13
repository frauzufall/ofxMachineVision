#pragma once

#include "ofConstants.h"

#if defined(TARGET_OSX) || defined(TARGET_LINUX)

#include "ofxUVC.h"
#include "ofQTKitGrabber.h"

#include "ofxMachineVision/Specification.h"
#include "Updating.h"

#include <chrono>
#include <ctime>

namespace ofxMachineVision {
	namespace Device {
		/**
		 \brief Implementation of Greg Borenstein's ofxUVC library as an ofxMachineVision::Device::Updating class
		 */
		class OSXUVC : public Updating {
		public:
			OSXUVC(int width = 1920, int height = 1080, float desiredFramerate = 30);
                        Specification open(int deviceID);
			bool startCapture() override;
			void stopCapture() override;
			void close() override;
			void setExposure(Microseconds exposure) override;
			void setGain(float percent) override;
			void setFocus(float percent) override;
			void setSharpness(float percent) override;
			
			void updateIsFrameNew() override;
			bool isFrameNew() override;
			shared_ptr<Frame> getFrame() override;
			
			//--
			void resetTimestamp();
		protected:
			ofQTKitGrabber device;
			ofxUVC controller;
			
			int deviceID;
			int width, height;
			float desiredFramerate;
			
			chrono::high_resolution_clock::time_point timerStart;
			long frameIndex;
			
			shared_ptr<Frame> frame;
		};
		
		class Webcam : public OSXUVC {
		public:
			string getTypeName() const override {
				return "Webcam";
			}
		};
	}
}

#endif
