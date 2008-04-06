/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef DISTRIBUTEDOBJECTBROKER_H_
#define DISTRIBUTEDOBJECTBROKER_H_

#include "system/lang.h"

#include "engine/util/Singleton.h"

#include "engine/service/StreamServiceThread.h"

#include "DistributedObjectDirectory.h"

#include "NamingDirectoryService.h"

#include "DistributedObjectBrokerClient.h"

#include "DOBPacketHandler.h"

#include "object/DistributedObject.h"
#include "object/DistributedObjectStub.h"
#include "object/DistributedObjectServant.h"
#include "object/DistributedObjectAdapter.h"

#include "object/DistributedObjectClassHelper.h"
#include "object/DistributedObjectClassHelperMap.h"

#include "object/DistributedMethod.h"

#include "object/ObjectNotDeployedException.h"

#include "packets/DeployObjectMessage.h"
#include "packets/MethodReturnMessage.h"

namespace engine {
  namespace ORB {

	class DistributedObjectBroker : public StreamServiceThread, public Singleton<DistributedObjectBroker> {
		static DistributedObjectBroker* impl;
	
		string address;
		NamingDirectoryService* namingDirectoryInterface;
		
		DistributedObjectClassHelperMap classMap;
	
		DistributedObjectDirectory objectDirectory;
	
		DOBPacketHandler* phandler;
		
	private:
		DistributedObjectBroker();
	
		virtual ~DistributedObjectBroker();

	public:
		static DistributedObjectBroker* initialize(const string& addr, int port = 44433);
		
		void init();
	
		void run();
		
		void shutdown();
	
		DistributedObjectBrokerClient* createConnection(Socket* sock, SocketAddress& addr);
		
		void registerClass(const string& name, DistributedObjectClassHelper* helper);
	
		// deployment methods
		DistributedObject* deploy(DistributedObjectServant* obj);
		DistributedObject* deploy(const string& name, DistributedObjectServant* obj);
		
		DistributedObject* lookUp(const string& name);
		DistributedObject* lookUp(uint64 objid);
		
		DistributedObjectStub* undeploy(const string& name);

		DistributedObjectAdapter* getObjectAdapter(const string& name);
		DistributedObjectAdapter* getObjectAdapter(uint64 oid);

		// getters
		/*inline bool hasRootDirectory() {
			return namingDirectoryInterface->isRootDirectory();
		}*/
		
		inline DistributedObjectClassHelperMap* getClassMap() {
			return &classMap;
		}
		
		inline DOBPacketHandler* getPacketHandler() {
			return phandler;
		}
		
		friend class NamingDirectoryService;
			
		friend class SingletonWrapper<DistributedObjectBroker>;
		
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*DISTRIBUTEDOBJECTBROKER_H_*/
