#include <mioc/SingletonContainer.h>

MIOC_BEGIN


ServiceContainerPtr SingletonContainer::GetContainer()
{
    if (_container == nullptr)
    {
        _container = ServiceContainer::New(_lazy);
    }
    return _container;
}

ServiceContainerPtr SingletonContainer::GetContainer(bool lazy)
{
    _lazy = lazy;
    return GetContainer();
}

std::shared_ptr<ServiceContainer> SingletonContainer::_container;
bool SingletonContainer::_lazy = DEFAULT_LAZINESS;


MIOC_END
