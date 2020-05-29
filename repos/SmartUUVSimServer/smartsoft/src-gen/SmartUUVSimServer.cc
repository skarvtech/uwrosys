//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#include "SmartUUVSimServer.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "SmartUUVSimServerAcePortFactory.hh"


// initialize static singleton pointer to zero
SmartUUVSimServer* SmartUUVSimServer::_smartUUVSimServer = 0;

// constructor
SmartUUVSimServer::SmartUUVSimServer()
{
	std::cout << "constructor of SmartUUVSimServer\n";
	
	// set all pointer members to NULL
	baseSatateQueryAnsw = NULL;
	baseSatateQueryAnswInputTaskTrigger = NULL;
	baseStateQueryHandler = NULL;
	baseStateServiceOut = NULL;
	baseStateTask = NULL;
	baseStateTaskTrigger = NULL;
	//coordinationPort = NULL;
	laserServiceOut = NULL;
	laserTask = NULL;
	laserTaskTrigger = NULL;
	localizationUpdateHandler = NULL;
	localizationUpdateServiceIn = NULL;
	localizationUpdateServiceInInputTaskTrigger = NULL;
	localizationUpdateServiceInUpcallManager = NULL;
	navVelServiceIn = NULL;
	navVelServiceInInputTaskTrigger = NULL;
	navVelServiceInUpcallManager = NULL;
	pollForGazeboConnection = NULL;
	pollForGazeboConnectionTrigger = NULL;
	//smartUUVSimServerParams = NULL;
	velocityInpuHandler = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "SmartUUVSimServer";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.baseSatateQueryAnsw.serviceName = "BaseSatateQueryAnsw";
	connections.baseSatateQueryAnsw.roboticMiddleware = "ACE_SmartSoft";
	connections.baseStateServiceOut.serviceName = "BaseStateServiceOut";
	connections.baseStateServiceOut.roboticMiddleware = "ACE_SmartSoft";
	connections.laserServiceOut.serviceName = "LaserServiceOut";
	connections.laserServiceOut.roboticMiddleware = "ACE_SmartSoft";
	connections.localizationUpdateServiceIn.serviceName = "LocalizationUpdateServiceIn";
	connections.localizationUpdateServiceIn.roboticMiddleware = "ACE_SmartSoft";
	connections.navVelServiceIn.serviceName = "NavVelServiceIn";
	connections.navVelServiceIn.roboticMiddleware = "ACE_SmartSoft";
	connections.baseStateTask.minActFreq = 10.0;
	connections.baseStateTask.maxActFreq = 40.0;
	connections.baseStateTask.trigger = "PeriodicTimer";
	connections.baseStateTask.periodicActFreq = 20.0;
	// scheduling default parameters
	connections.baseStateTask.scheduler = "DEFAULT";
	connections.baseStateTask.priority = -1;
	connections.baseStateTask.cpuAffinity = -1;
	// scheduling default parameters
	connections.laserTask.scheduler = "DEFAULT";
	connections.laserTask.priority = -1;
	connections.laserTask.cpuAffinity = -1;
	connections.pollForGazeboConnection.minActFreq = 0.0;
	connections.pollForGazeboConnection.maxActFreq = 0.0;
	// scheduling default parameters
	connections.pollForGazeboConnection.scheduler = "DEFAULT";
	connections.pollForGazeboConnection.priority = -1;
	connections.pollForGazeboConnection.cpuAffinity = -1;
	connections.localizationUpdateHandler.prescale = 1;
	connections.velocityInpuHandler.prescale = 1;
	
	// initialize members of OpcUaBackendComponentGeneratorExtension
	
	// initialize members of PlainOpcUaSmartUUVSimServerExtension
	
	// initialize members of SmartUUVSimServerROSExtension
	
}

void SmartUUVSimServer::addPortFactory(const std::string &name, SmartUUVSimServerPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void SmartUUVSimServer::addExtension(SmartUUVSimServerExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* SmartUUVSimServer::getComponentImpl()
{
	return dynamic_cast<SmartUUVSimServerAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void SmartUUVSimServer::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}




/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode SmartUUVSimServer::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void SmartUUVSimServer::startAllTasks() {
	// start task BaseStateTask
	if(connections.baseStateTask.scheduler != "DEFAULT") {
		ACE_Sched_Params baseStateTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.baseStateTask.scheduler == "FIFO") {
			baseStateTask_SchedParams.policy(ACE_SCHED_FIFO);
			baseStateTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.baseStateTask.scheduler == "RR") {
			baseStateTask_SchedParams.policy(ACE_SCHED_RR);
			baseStateTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		baseStateTask->start(baseStateTask_SchedParams, connections.baseStateTask.cpuAffinity);
	} else {
		baseStateTask->start();
	}
	// start task LaserTask
	if(connections.laserTask.scheduler != "DEFAULT") {
		ACE_Sched_Params laserTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.laserTask.scheduler == "FIFO") {
			laserTask_SchedParams.policy(ACE_SCHED_FIFO);
			laserTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.laserTask.scheduler == "RR") {
			laserTask_SchedParams.policy(ACE_SCHED_RR);
			laserTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		laserTask->start(laserTask_SchedParams, connections.laserTask.cpuAffinity);
	} else {
		laserTask->start();
	}
	// start task PollForGazeboConnection
	if(connections.pollForGazeboConnection.scheduler != "DEFAULT") {
		ACE_Sched_Params pollForGazeboConnection_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.pollForGazeboConnection.scheduler == "FIFO") {
			pollForGazeboConnection_SchedParams.policy(ACE_SCHED_FIFO);
			pollForGazeboConnection_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.pollForGazeboConnection.scheduler == "RR") {
			pollForGazeboConnection_SchedParams.policy(ACE_SCHED_RR);
			pollForGazeboConnection_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		pollForGazeboConnection->start(pollForGazeboConnection_SchedParams, connections.pollForGazeboConnection.cpuAffinity);
	} else {
		pollForGazeboConnection->start();
	}
}

/**
 * Start all timers contained in this component
 */
void SmartUUVSimServer::startAllTimers() {
}


Smart::TaskTriggerSubject* SmartUUVSimServer::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "LocalizationUpdateServiceIn") return localizationUpdateServiceInInputTaskTrigger;
	if(client == "NavVelServiceIn") return navVelServiceInInputTaskTrigger;
	
	return NULL;
}


void SmartUUVSimServer::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getParameters() << std::endl;
		
		// initializations of OpcUaBackendComponentGeneratorExtension
		
		// initializations of PlainOpcUaSmartUUVSimServerExtension
		
		// initializations of SmartUUVSimServerROSExtension
		
		
		// initialize all registered port-factories
		for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
		{
			portFactory->second->initialize(this, argc, argv);
		}
		
		// initialize all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->initialize(this, argc, argv);
		}
		
		SmartUUVSimServerPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<SmartUUVSimServerAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition SmartUUVSimServer is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		baseSatateQueryAnsw = portFactoryRegistry[connections.baseSatateQueryAnsw.roboticMiddleware]->createBaseSatateQueryAnsw(connections.baseSatateQueryAnsw.serviceName);
		baseSatateQueryAnswInputTaskTrigger = new Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState>(baseSatateQueryAnsw);
		baseStateServiceOut = portFactoryRegistry[connections.baseStateServiceOut.roboticMiddleware]->createBaseStateServiceOut(connections.baseStateServiceOut.serviceName);
		laserServiceOut = portFactoryRegistry[connections.laserServiceOut.roboticMiddleware]->createLaserServiceOut(connections.laserServiceOut.serviceName);
		localizationUpdateServiceIn = portFactoryRegistry[connections.localizationUpdateServiceIn.roboticMiddleware]->createLocalizationUpdateServiceIn(connections.localizationUpdateServiceIn.serviceName);
		navVelServiceIn = portFactoryRegistry[connections.navVelServiceIn.roboticMiddleware]->createNavVelServiceIn(connections.navVelServiceIn.serviceName);
		
		// create client ports
		
		// create InputTaskTriggers and UpcallManagers
		localizationUpdateServiceInInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommBasePositionUpdate>(localizationUpdateServiceIn);
		localizationUpdateServiceInUpcallManager = new LocalizationUpdateServiceInUpcallManager(localizationUpdateServiceIn);
		navVelServiceInInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommNavigationVelocity>(navVelServiceIn);
		navVelServiceInUpcallManager = new NavVelServiceInUpcallManager(navVelServiceIn);
		
		// create input-handler
		localizationUpdateHandler = new LocalizationUpdateHandler(localizationUpdateServiceIn, connections.localizationUpdateHandler.prescale);
		velocityInpuHandler = new VelocityInpuHandler(navVelServiceIn, connections.velocityInpuHandler.prescale);
		
		// create request-handlers
		baseStateQueryHandler = new BaseStateQueryHandler(baseSatateQueryAnsw);
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task BaseStateTask
		baseStateTask = new BaseStateTask(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.baseStateTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.baseStateTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(baseStateTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				baseStateTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task BaseStateTask" << std::endl;
			}
		} else if(connections.baseStateTask.trigger == "DataTriggered") {
			baseStateTaskTrigger = getInputTaskTriggerFromString(connections.baseStateTask.inPortRef);
			if(baseStateTaskTrigger != NULL) {
				baseStateTaskTrigger->attach(baseStateTask, connections.baseStateTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.baseStateTask.inPortRef << " as activation source for Task BaseStateTask" << std::endl;
			}
		} else
		{
			// setup default task-trigger as PeriodicTimer
			Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
			int microseconds = 1000*1000 / 20.0;
			if(microseconds > 0) {
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				triggerPtr->attach(baseStateTask);
				// store trigger in class member
				baseStateTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task BaseStateTask" << std::endl;
			}
		}
		
		// create Task LaserTask
		laserTask = new LaserTask(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		
		// create Task PollForGazeboConnection
		pollForGazeboConnection = new PollForGazeboConnection(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.pollForGazeboConnection.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.pollForGazeboConnection.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(pollForGazeboConnection);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				pollForGazeboConnectionTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task PollForGazeboConnection" << std::endl;
			}
		} else if(connections.pollForGazeboConnection.trigger == "DataTriggered") {
			pollForGazeboConnectionTrigger = getInputTaskTriggerFromString(connections.pollForGazeboConnection.inPortRef);
			if(pollForGazeboConnectionTrigger != NULL) {
				pollForGazeboConnectionTrigger->attach(pollForGazeboConnection, connections.pollForGazeboConnection.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.pollForGazeboConnection.inPortRef << " as activation source for Task PollForGazeboConnection" << std::endl;
			}
		} 
		
		
		// link observers with subjects
		baseStateTask->attach_interaction_observer(baseStateQueryHandler);
		localizationUpdateHandler->attach_interaction_observer(baseStateTask);
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void SmartUUVSimServer::run()
{
	stateSlave->acquire("init");
	// startup all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onStartup();
	}
	
	// startup all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onStartup();
	}
	stateSlave->release("init");
	
	// do not call this handler within the init state (see above) as this handler internally calls setStartupFinished() (this should be fixed in future)
	compHandler.onStartup();
	
	// this call blocks until the component is commanded to shutdown
	stateSlave->acquire("shutdown");
	
	// shutdown all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onShutdown();
	}
	
	// shutdown all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onShutdown();
	}
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	stateSlave->release("shutdown");
}

// clean-up component's resources
void SmartUUVSimServer::fini()
{
	// unlink all observers
	baseStateTask->detach_interaction_observer(baseStateQueryHandler);
	localizationUpdateHandler->detach_interaction_observer(baseStateTask);
	
	// destroy all task instances
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(baseStateTaskTrigger != NULL){
		baseStateTaskTrigger->detach(baseStateTask);
		delete baseStateTask;
	}
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(laserTaskTrigger != NULL){
		laserTaskTrigger->detach(laserTask);
		delete laserTask;
	}
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(pollForGazeboConnectionTrigger != NULL){
		pollForGazeboConnectionTrigger->detach(pollForGazeboConnection);
		delete pollForGazeboConnection;
	}

	// destroy all input-handler
	delete localizationUpdateHandler;
	delete velocityInpuHandler;

	// destroy InputTaskTriggers and UpcallManagers
	delete localizationUpdateServiceInInputTaskTrigger;
	delete localizationUpdateServiceInUpcallManager;
	delete navVelServiceInInputTaskTrigger;
	delete navVelServiceInUpcallManager;

	// destroy client ports

	// destroy server ports
	delete baseSatateQueryAnsw;
	delete baseSatateQueryAnswInputTaskTrigger;
	delete baseStateServiceOut;
	delete laserServiceOut;
	delete localizationUpdateServiceIn;
	delete navVelServiceIn;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	delete baseStateQueryHandler;
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	delete param;
	

	// destroy all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->destroy();
	}

	// destroy all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->destroy();
	}
	
	// destruction of OpcUaBackendComponentGeneratorExtension
	
	// destruction of PlainOpcUaSmartUUVSimServerExtension
	
	// destruction of SmartUUVSimServerROSExtension
	
}

void SmartUUVSimServer::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("SmartUUVSimServer.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load SmartUUVSimServer.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: SmartUUVSimServer.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		
		// load parameters for server BaseSatateQueryAnsw
		parameter.getString("BaseSatateQueryAnsw", "serviceName", connections.baseSatateQueryAnsw.serviceName);
		if(parameter.checkIfParameterExists("BaseSatateQueryAnsw", "roboticMiddleware")) {
			parameter.getString("BaseSatateQueryAnsw", "roboticMiddleware", connections.baseSatateQueryAnsw.roboticMiddleware);
		}
		// load parameters for server BaseStateServiceOut
		parameter.getString("BaseStateServiceOut", "serviceName", connections.baseStateServiceOut.serviceName);
		if(parameter.checkIfParameterExists("BaseStateServiceOut", "roboticMiddleware")) {
			parameter.getString("BaseStateServiceOut", "roboticMiddleware", connections.baseStateServiceOut.roboticMiddleware);
		}
		// load parameters for server LaserServiceOut
		parameter.getString("LaserServiceOut", "serviceName", connections.laserServiceOut.serviceName);
		if(parameter.checkIfParameterExists("LaserServiceOut", "roboticMiddleware")) {
			parameter.getString("LaserServiceOut", "roboticMiddleware", connections.laserServiceOut.roboticMiddleware);
		}
		// load parameters for server LocalizationUpdateServiceIn
		parameter.getString("LocalizationUpdateServiceIn", "serviceName", connections.localizationUpdateServiceIn.serviceName);
		if(parameter.checkIfParameterExists("LocalizationUpdateServiceIn", "roboticMiddleware")) {
			parameter.getString("LocalizationUpdateServiceIn", "roboticMiddleware", connections.localizationUpdateServiceIn.roboticMiddleware);
		}
		// load parameters for server NavVelServiceIn
		parameter.getString("NavVelServiceIn", "serviceName", connections.navVelServiceIn.serviceName);
		if(parameter.checkIfParameterExists("NavVelServiceIn", "roboticMiddleware")) {
			parameter.getString("NavVelServiceIn", "roboticMiddleware", connections.navVelServiceIn.roboticMiddleware);
		}
		
		// load parameters for task BaseStateTask
		parameter.getDouble("BaseStateTask", "minActFreqHz", connections.baseStateTask.minActFreq);
		parameter.getDouble("BaseStateTask", "maxActFreqHz", connections.baseStateTask.maxActFreq);
		parameter.getString("BaseStateTask", "triggerType", connections.baseStateTask.trigger);
		if(connections.baseStateTask.trigger == "PeriodicTimer") {
			parameter.getDouble("BaseStateTask", "periodicActFreqHz", connections.baseStateTask.periodicActFreq);
		} else if(connections.baseStateTask.trigger == "DataTriggered") {
			parameter.getString("BaseStateTask", "inPortRef", connections.baseStateTask.inPortRef);
			parameter.getInteger("BaseStateTask", "prescale", connections.baseStateTask.prescale);
		}
		if(parameter.checkIfParameterExists("BaseStateTask", "scheduler")) {
			parameter.getString("BaseStateTask", "scheduler", connections.baseStateTask.scheduler);
		}
		if(parameter.checkIfParameterExists("BaseStateTask", "priority")) {
			parameter.getInteger("BaseStateTask", "priority", connections.baseStateTask.priority);
		}
		if(parameter.checkIfParameterExists("BaseStateTask", "cpuAffinity")) {
			parameter.getInteger("BaseStateTask", "cpuAffinity", connections.baseStateTask.cpuAffinity);
		}
		// load parameters for task LaserTask
		if(parameter.checkIfParameterExists("LaserTask", "scheduler")) {
			parameter.getString("LaserTask", "scheduler", connections.laserTask.scheduler);
		}
		if(parameter.checkIfParameterExists("LaserTask", "priority")) {
			parameter.getInteger("LaserTask", "priority", connections.laserTask.priority);
		}
		if(parameter.checkIfParameterExists("LaserTask", "cpuAffinity")) {
			parameter.getInteger("LaserTask", "cpuAffinity", connections.laserTask.cpuAffinity);
		}
		// load parameters for task PollForGazeboConnection
		parameter.getDouble("PollForGazeboConnection", "minActFreqHz", connections.pollForGazeboConnection.minActFreq);
		parameter.getDouble("PollForGazeboConnection", "maxActFreqHz", connections.pollForGazeboConnection.maxActFreq);
		parameter.getString("PollForGazeboConnection", "triggerType", connections.pollForGazeboConnection.trigger);
		if(connections.pollForGazeboConnection.trigger == "PeriodicTimer") {
			parameter.getDouble("PollForGazeboConnection", "periodicActFreqHz", connections.pollForGazeboConnection.periodicActFreq);
		} else if(connections.pollForGazeboConnection.trigger == "DataTriggered") {
			parameter.getString("PollForGazeboConnection", "inPortRef", connections.pollForGazeboConnection.inPortRef);
			parameter.getInteger("PollForGazeboConnection", "prescale", connections.pollForGazeboConnection.prescale);
		}
		if(parameter.checkIfParameterExists("PollForGazeboConnection", "scheduler")) {
			parameter.getString("PollForGazeboConnection", "scheduler", connections.pollForGazeboConnection.scheduler);
		}
		if(parameter.checkIfParameterExists("PollForGazeboConnection", "priority")) {
			parameter.getInteger("PollForGazeboConnection", "priority", connections.pollForGazeboConnection.priority);
		}
		if(parameter.checkIfParameterExists("PollForGazeboConnection", "cpuAffinity")) {
			parameter.getInteger("PollForGazeboConnection", "cpuAffinity", connections.pollForGazeboConnection.cpuAffinity);
		}
		if(parameter.checkIfParameterExists("LocalizationUpdateHandler", "prescale")) {
			parameter.getInteger("LocalizationUpdateHandler", "prescale", connections.localizationUpdateHandler.prescale);
		}
		if(parameter.checkIfParameterExists("VelocityInpuHandler", "prescale")) {
			parameter.getInteger("VelocityInpuHandler", "prescale", connections.velocityInpuHandler.prescale);
		}
		
		// load parameters for OpcUaBackendComponentGeneratorExtension
		
		// load parameters for PlainOpcUaSmartUUVSimServerExtension
		
		// load parameters for SmartUUVSimServerROSExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
		}
		
		paramHandler.loadParameter(parameter);
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
