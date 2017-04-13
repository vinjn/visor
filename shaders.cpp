#include "precompiled.h"
#include "premade_shaders.h"

VKAPI_ATTR VkResult VKAPI_CALL vkCreateShaderModule(VkDevice device,
                                                    const VkShaderModuleCreateInfo *pCreateInfo,
                                                    const VkAllocationCallbacks *pAllocator,
                                                    VkShaderModule *pShaderModule)
{
  VkShaderModule ret = new VkShaderModule_T;

  uint32_t hash = hashSPV(pCreateInfo->pCode, pCreateInfo->codeSize / sizeof(uint32_t));

  switch(hash)
  {
    case 2469737040:
    {
      ret->func = (Shader)&vkcube_vs;
      break;
    }
    case 676538074:
    {
      ret->func = (Shader)&vkcube_fs;
      break;
    }
    default:
    {
      printf("Unrecognised/hacked shader! whoops!");
      return VK_ERROR_DEVICE_LOST;
    }
  }

  *pShaderModule = ret;
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule,
                                                 const VkAllocationCallbacks *pAllocator)
{
  delete shaderModule;
}

VKAPI_ATTR VkResult VKAPI_CALL
vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount,
                          const VkGraphicsPipelineCreateInfo *pCreateInfos,
                          const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines)
{
  for(uint32_t i = 0; i < createInfoCount; i++)
  {
    VkPipeline ret = new VkPipeline_T;
    for(uint32_t s = 0; s < pCreateInfos[i].stageCount; s++)
    {
      if(pCreateInfos[i].pStages[s].stage == VK_SHADER_STAGE_VERTEX_BIT)
        ret->vs = (VertexShader)pCreateInfos[i].pStages[s].module->func;
      else if(pCreateInfos[i].pStages[s].stage == VK_SHADER_STAGE_FRAGMENT_BIT)
        ret->fs = (FragmentShader)pCreateInfos[i].pStages[s].module->func;
    }
    pPipelines[i] = ret;
  }
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL
vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount,
                         const VkComputePipelineCreateInfo *pCreateInfos,
                         const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines)
{
  for(uint32_t i = 0; i < createInfoCount; i++)
  {
    VkPipeline ret = new VkPipeline_T;
    pPipelines[i] = ret;
  }
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipeline(VkDevice device, VkPipeline pipeline,
                                             const VkAllocationCallbacks *pAllocator)
{
  delete pipeline;
}
