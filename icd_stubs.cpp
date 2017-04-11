#include "precompiled.h"

VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(const VkInstanceCreateInfo *pCreateInfo,
                                                const VkAllocationCallbacks *pAllocator,
                                                VkInstance *pInstance)
{
  *pInstance = (VkInstance) new VK_LOADER_DATA;
  set_loader_magic_value(*pInstance);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyInstance(VkInstance instance,
                                             const VkAllocationCallbacks *pAllocator)
{
  delete(VK_LOADER_DATA *)instance;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(VkPhysicalDevice physicalDevice,
                                              const VkDeviceCreateInfo *pCreateInfo,
                                              const VkAllocationCallbacks *pAllocator,
                                              VkDevice *pDevice)
{
  VkDevice dev = new VkDevice_T;
  assert((void *)dev == &dev->loaderMagic);
  set_loader_magic_value(dev);

  // we only have 1 queue family, there should only be 1 info
  assert(pCreateInfo->queueCreateInfoCount == 1);
  dev->queues.resize(pCreateInfo->pQueueCreateInfos[0].queueCount);

  for(uint32_t i = 0; i < pCreateInfo->pQueueCreateInfos[0].queueCount; i++)
  {
    dev->queues[i] = new VK_LOADER_DATA;
    set_loader_magic_value(dev->queues[i]);
  }

  *pDevice = dev;
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(VkDevice device, const VkAllocationCallbacks *pAllocator)
{
  for(VK_LOADER_DATA *q : device->queues)
    delete q;

  delete device;
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex,
                                            uint32_t queueIndex, VkQueue *pQueue)
{
  assert(queueFamilyIndex == 0);

  *pQueue = (VkQueue)device->queues[queueIndex];
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(VkDevice device, const VkFenceCreateInfo *pCreateInfo,
                                             const VkAllocationCallbacks *pAllocator, VkFence *pFence)
{
  // TODO but for now return unique values
  static uint64_t nextFence = 1;
  *pFence = (VkFence)(nextFence++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyFence(VkDevice device, VkFence fence,
                                          const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSemaphore(VkDevice device,
                                                 const VkSemaphoreCreateInfo *pCreateInfo,
                                                 const VkAllocationCallbacks *pAllocator,
                                                 VkSemaphore *pSemaphore)
{
  // TODO but for now return unique values
  static uint64_t nextSemaphore = 1;
  *pSemaphore = (VkSemaphore)(nextSemaphore++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroySemaphore(VkDevice device, VkSemaphore semaphore,
                                              const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSampler(VkDevice device,
                                               const VkSamplerCreateInfo *pCreateInfo,
                                               const VkAllocationCallbacks *pAllocator,
                                               VkSampler *pSampler)
{
  // TODO but for now return unique values
  static uint64_t nextSampler = 1;
  *pSampler = (VkSampler)(nextSampler++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroySampler(VkDevice device, VkSampler sampler,
                                            const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorSetLayout(
    VkDevice device, const VkDescriptorSetLayoutCreateInfo *pCreateInfo,
    const VkAllocationCallbacks *pAllocator, VkDescriptorSetLayout *pDescriptorSetLayout)
{
  // TODO but for now return unique values
  static uint64_t nextDescriptorSetLayout = 1;
  *pDescriptorSetLayout = (VkDescriptorSetLayout)(nextDescriptorSetLayout++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(VkDevice device,
                                                        VkDescriptorSetLayout descriptorSetLayout,
                                                        const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineLayout(VkDevice device,
                                                      const VkPipelineLayoutCreateInfo *pCreateInfo,
                                                      const VkAllocationCallbacks *pAllocator,
                                                      VkPipelineLayout *pPipelineLayout)
{
  // TODO but for now return unique values
  static uint64_t nextPipelineLayout = 1;
  *pPipelineLayout = (VkPipelineLayout)(nextPipelineLayout++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout,
                                                   const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateShaderModule(VkDevice device,
                                                    const VkShaderModuleCreateInfo *pCreateInfo,
                                                    const VkAllocationCallbacks *pAllocator,
                                                    VkShaderModule *pShaderModule)
{
  // TODO but for now return unique values
  static uint64_t nextShaderModule = 1;
  *pShaderModule = (VkShaderModule)(nextShaderModule++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule,
                                                 const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineCache(VkDevice device,
                                                     const VkPipelineCacheCreateInfo *pCreateInfo,
                                                     const VkAllocationCallbacks *pAllocator,
                                                     VkPipelineCache *pPipelineCache)
{
  // TODO but for now return unique values
  static uint64_t nextPipelineCache = 1;
  *pPipelineCache = (VkPipelineCache)(nextPipelineCache++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache,
                                                  const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL
vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount,
                          const VkGraphicsPipelineCreateInfo *pCreateInfos,
                          const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines)
{
  // TODO but for now return unique values
  static uint64_t nextGraphicsPipeline = 1;
  for(uint32_t i = 0; i < createInfoCount; i++)
    pPipelines[i] = (VkPipeline)(nextGraphicsPipeline++);
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL
vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount,
                         const VkComputePipelineCreateInfo *pCreateInfos,
                         const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines)
{
  // TODO but for now return unique values
  static uint64_t nextComputePipeline = 1;
  for(uint32_t i = 0; i < createInfoCount; i++)
    pPipelines[i] = (VkPipeline)(nextComputePipeline++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipeline(VkDevice device, VkPipeline pipeline,
                                             const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorPool(VkDevice device,
                                                      const VkDescriptorPoolCreateInfo *pCreateInfo,
                                                      const VkAllocationCallbacks *pAllocator,
                                                      VkDescriptorPool *pDescriptorPool)
{
  // TODO but for now return unique values
  static uint64_t nextDescriptorPool = 1;
  *pDescriptorPool = (VkDescriptorPool)(nextDescriptorPool++);
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool sampler,
                                                   const VkAllocationCallbacks *pAllocator)
{
  // nothing to do
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateDescriptorSets(VkDevice device,
                                                        const VkDescriptorSetAllocateInfo *pAllocateInfo,
                                                        VkDescriptorSet *pDescriptorSets)
{
  // TODO but for now return unique values
  static uint64_t nextDescriptorSet = 1;
  for(uint32_t i = 0; i < pAllocateInfo->descriptorSetCount; i++)
    pDescriptorSets[0] = (VkDescriptorSet)(nextDescriptorSet++);
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool,
                                                    uint32_t descriptorSetCount,
                                                    const VkDescriptorSet *pDescriptorSets)
{
  // nothing to do
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount,
                                                  const VkWriteDescriptorSet *pDescriptorWrites,
                                                  uint32_t descriptorCopyCount,
                                                  const VkCopyDescriptorSet *pDescriptorCopies)
{
  // TODO
}

VKAPI_ATTR VkResult VKAPI_CALL vkWaitForFences(VkDevice device, uint32_t fenceCount,
                                               const VkFence *pFences, VkBool32 waitAll,
                                               uint64_t timeout)
{
  // TODO
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetFences(VkDevice device, uint32_t fenceCount,
                                             const VkFence *pFences)
{
  // TODO
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkDeviceWaitIdle(VkDevice device)
{
  // TODO
  return VK_SUCCESS;
}