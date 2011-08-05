#include "precomp.h"

CNodeHttpModuleFactory::CNodeHttpModuleFactory() 
	: applicationManager(NULL)
{
}

CNodeHttpModuleFactory::~CNodeHttpModuleFactory()
{
	if (NULL != this->applicationManager)
	{
		delete this->applicationManager;
		this->applicationManager = NULL;
	}
}

HRESULT CNodeHttpModuleFactory::Initialize(IHttpServer* server, HTTP_MODULE_ID moduleId) 
{
	return (NULL == (applicationManager = new CNodeApplicationManager(server, moduleId))) ? ERROR_NOT_ENOUGH_MEMORY : S_OK;
}

HRESULT CNodeHttpModuleFactory::GetHttpModule(
    OUT CHttpModule **ppModule, 
    IN IModuleAllocator *
)
{
	HRESULT hr;

    ErrorIf(NULL == (*ppModule = new CNodeHttpModule(this->applicationManager)), ERROR_NOT_ENOUGH_MEMORY);

    return S_OK;
Error:
	return hr;
}

void CNodeHttpModuleFactory::Terminate()
{
    delete this;
}