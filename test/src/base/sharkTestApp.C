//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "sharkTestApp.h"
#include "sharkApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<sharkTestApp>()
{
  InputParameters params = validParams<sharkApp>();
  return params;
}

sharkTestApp::sharkTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  sharkApp::registerObjectDepends(_factory);
  sharkApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  sharkApp::associateSyntaxDepends(_syntax, _action_factory);
  sharkApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  sharkApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    sharkTestApp::registerObjects(_factory);
    sharkTestApp::associateSyntax(_syntax, _action_factory);
    sharkTestApp::registerExecFlags(_factory);
  }
}

sharkTestApp::~sharkTestApp() {}

void
sharkTestApp::registerApps()
{
  registerApp(sharkApp);
  registerApp(sharkTestApp);
}

void
sharkTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
sharkTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
sharkTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
sharkTestApp__registerApps()
{
  sharkTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
sharkTestApp__registerObjects(Factory & factory)
{
  sharkTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
sharkTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  sharkTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
sharkTestApp__registerExecFlags(Factory & factory)
{
  sharkTestApp::registerExecFlags(factory);
}
