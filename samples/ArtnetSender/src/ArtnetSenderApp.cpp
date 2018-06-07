#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "CinderLibArtnet.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ArtnetSenderApp : public App {
public:
	void setup();
	void update();
	void draw();

    ciArtnet::Node    node;
};

void ArtnetSenderApp::setup()
{
	printf("printf\n");
	cout << "cout" << endl;;
	console() << "console" << endl;
	CI_LOG_I("Log");

    node.setNumUniverses(1);//optional, setup() will create a single universe 1 at index 0 otherwise
    node.setUniverseAtIndex(0, 0);//optional, otherwise universes start at 1

	// THIS NEEDS TO BE OUR IP!
	node.setup("10.0.1.65", true);//need to enable sendRaw if sending to multiple artnet devices
	//node.setup("", true);//need to enable sendRaw if sending to multiple artnet devices
	//"192.168.42.182"
}


void ArtnetSenderApp::update()
{
    //create some test data
    const int length = 512;
    unsigned char data[length];
    float val = math<float>::clamp( (float)getMousePos().x/ getWindowWidth() -1 );
    for (int i=0; i<length; i++) data[i] = val * 255;
    
    gl::clear( Color( val, val, val ) );

    node.updateData(data, length);//if only using one universe
    //node.updateDataByIndex(0, data, length);
    //node.updateDataByUniverse(universe, data, length);

    node.send();
}

void ArtnetSenderApp::draw()
{
    
}


auto settingsFunc = [](App::Settings *settings) {
#if defined( CINDER_MSW )
	settings->setConsoleWindowEnabled();
#endif
	settings->setMultiTouchEnabled(false);
};

CINDER_APP( ArtnetSenderApp, RendererGl, settingsFunc)
