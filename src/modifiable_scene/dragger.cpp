#include "dragger.h"
#include <osg/Material>
#include <osg/BlendFunc>

namespace modifiable_scene{

DualPlaneDragger::DualPlaneDragger()
{
    _plane_dragger1 = new osgManipulator::Translate2DDragger(osg::Plane(osg::Vec3f(0.f, 0.f, 1.f), 1.f));
    _plane_dragger2 = new osgManipulator::Translate2DDragger(osg::Plane(osg::Vec3f(0.f, 1.f, 0.f), 1.f));
    addChild(_plane_dragger1.get());
    addDragger(_plane_dragger1.get());
    addChild(_plane_dragger2.get());
    addDragger(_plane_dragger2.get());

    _plane_dragger1->setParentDragger(getParentDragger());
    _plane_dragger2->setParentDragger(getParentDragger());
}

void DualPlaneDragger::setColor(const osg::Vec4 &color)
{
    _plane_dragger1->setColor(color);
    _plane_dragger2->setColor(color);
}

/*
void DualPlaneDragger::setParentDragger(Dragger *parent){
    _plane_dragger1->setParentDragger(parent);
    _plane_dragger2->setParentDragger(parent);
}
*/
DualPlaneDragger::~DualPlaneDragger(){

}


void DualPlaneDragger::setupDefaultGeometry()
{
    _plane_dragger1->setupDefaultGeometry();
    _plane_dragger2->setupDefaultGeometry();
}

Dragger::Dragger()
{
    _orientation_dragger = new TrackballDragger(false);
    addChild(_orientation_dragger.get());
    addDragger(_orientation_dragger.get());

    osg::MatrixTransform* tr = new osg::MatrixTransform();
    tr->setMatrix(osg::Matrix::scale(2.1,2.1,2.1));
    _position_dragger = new DualPlaneDragger();
    tr->addChild(_position_dragger);
    addChild(tr);
    addDragger(_position_dragger.get());

    _orientation_dragger->setParentDragger(this);
    _position_dragger->setParentDragger(this);

    set_apprearence();
}

void Dragger::set_apprearence(){
    osg::StateSet* state = getOrCreateStateSet();
    //state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);


    _orientation_dragger->setColor(osg::Vec4f(0,1,1,0.5));
    _position_dragger->setColor(osg::Vec4f(0,1,1,.5));


    setStateSet(state);
}

Dragger::~Dragger(){

}

void Dragger::setupDefaultGeometry()
{
    _orientation_dragger->setupDefaultGeometry();
    _position_dragger->setupDefaultGeometry();
}

}
