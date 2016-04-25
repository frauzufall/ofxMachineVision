#pragma once

#include "ofConstants.h"

#if defined(TARGET_OSX) || defined(TARGET_LINUX)

//#include "ofxUVC.h"
#include "ofVideoGrabber.h"

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

			struct InitialisationSettings : Base::InitialisationSettings {
			public:
				InitialisationSettings() {
					add(width.set("Width", 1920));
					add(height.set("Height", 1080));
					add(idealFrameRate.set("Ideal frame rate", 30));
				}

				ofParameter<int> width;
				ofParameter<int> height;
				ofParameter<int> idealFrameRate;
			};

			virtual string getTypeName() const override;
			shared_ptr<Base::InitialisationSettings> getDefaultSettings() override {
				return make_shared<InitialisationSettings>();
			}

			ofxMachineVision::Specification open(shared_ptr<Base::InitialisationSettings> = nullptr) override;

			//Specification open(int deviceID) override;
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
			ofVideoGrabber device;
//			ofxUVC controller;

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
