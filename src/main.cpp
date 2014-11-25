#include "var.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class xApp : public ofBaseApp{

	public:
		ofxPanel gui;
		ofxSlider<float> timer;
		ofxButton explosion;
		
		ofxAssimpModelLoader model;

		int   counter = 0;
		bool  stopnoise,stopanim = true;
		float speedanim;

		void setup() {
		        ofSetFrameRate(60);
		        ofSetVerticalSync(true);

			gui.setup();
			gui.add(timer.setup("timer",0.,20.,-20.));
			gui.add(explosion.setup("explosion",false));


			bAnimate = false;
			bAnimateMouse = false;
			animationPosition = 0;
			model.loadModel("model/model.dae");
			model.setPosition( ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0 );
			model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
			model.playAllAnimations();
			if(!bAnimate) {
			        model.setPausedForAllAnimations(true);
			}

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();

		        shader.setGeometryInputType(GL_LINES);
		        shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
		        shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);
		        shader.load( "shaders/EXPLOSION.vert", "shaders/EXPLOSION.frag", "shaders/EXPLOSION.geom");
		        printf("Maximum number of output vertices support is: %i\n", shader.getGeometryMaxOutputCount());

			camera.setFarClip(100000);
			speedanim=60;
		}

		void update() {
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			model.update();
			if(stopanim){
		        	animationPosition = ofMap(counter,0,speedanim,0.0,1.0);
				counter++;
				if(counter>speedanim)
					counter=0;
				model.setPositionForAllAnimations(animationPosition);
			}
		}

		float increment=0.,stop=555.,inc=2.,stopinc=12.;
		void draw() {
			ofBackgroundGradient( ofColor(210), ofColor(10));

			ofEnableDepthTest();
			camera.begin();
			shader.begin();
			if(!explosion){
			      	shader.setUniform1f("time", timer ); 
				increment=0.;
				inc=0.;
			}
			else{
				increment-=inc;
			      	shader.setUniform1f("time", increment ); 
				if(increment>stop)
					increment=stop;
				inc-=.18;
				if(inc>stopinc)
					inc=stopinc;
			}
			shader.setUniformMatrix4f("projection",camera.getProjectionMatrix());
			shader.setUniformMatrix4f("modelview", camera.getModelViewMatrix() );

				  ofPushMatrix();
				  ofTranslate(model.getPosition().x+100, model.getPosition().y, 60);
				  ofTranslate(-model.getPosition().x, -model.getPosition().y, 60);
				  model.drawFaces();
				  ofPopMatrix();

			shader.end();
			ofDisableDepthTest();
			camera.end();

			gui.draw();
		}

		void keyPressed(int key) {
		        switch (key) {
				case 'f':
					ofToggleFullscreen();
					break;
		                default:
		                        break;
		        }
		}

};

int main(){
       ofAppGLFWWindow window;
       ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
       ofRunApp( new xApp());
}
