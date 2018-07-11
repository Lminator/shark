#include "sharkApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<sharkApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

sharkApp::sharkApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  sharkApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  sharkApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  sharkApp::registerExecFlags(_factory);
}

sharkApp::~sharkApp() {}

void
sharkApp::registerApps()
{
  registerApp(sharkApp);
}

void
sharkApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"sharkApp"});
}

void
sharkApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"sharkApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
sharkApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
sharkApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
sharkApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
sharkApp__registerApps()
{
  sharkApp::registerApps();
}

extern "C" void
sharkApp__registerObjects(Factory & factory)
{
  sharkApp::registerObjects(factory);
}

extern "C" void
sharkApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  sharkApp::associateSyntax(syntax, action_factory);
}

extern "C" void
sharkApp__registerExecFlags(Factory & factory)
{
  sharkApp::registerExecFlags(factory);
}
