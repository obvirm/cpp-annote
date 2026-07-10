// Minimal DirectML C API declarations for cpp-annote.
// Avoids pulling in dml_provider_factory.h (which requires the Windows SDK
// d3d12.h / DirectML.h). We only need:
//   - the OrtDmlApi struct (function pointers, forward-declared D3D types)
//   - the OrtApi::GetExecutionProviderApi entry used to resolve it at runtime
// so we never statically link against onnxruntime_providers_dml.lib.
#ifndef ORT_DML_CAPI_H
#define ORT_DML_CAPI_H

#include "onnxruntime_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations (the real types live in the Windows SDK; we only need
// opaque pointers for the API struct below).
struct IDMLDevice;
typedef struct IDMLDevice IDMLDevice;
struct ID3D12CommandQueue;
typedef struct ID3D12CommandQueue ID3D12CommandQueue;

// DML EP device options (DML2). We only use the default (device_id path via
// OrtDmlApi::SessionOptionsAppendExecutionProvider_DML).
struct OrtDmlDeviceOptions;
typedef struct OrtDmlDeviceOptions OrtDmlDeviceOptions;

// The DirectML execution provider API, obtained via
// OrtApi::GetExecutionProviderApi("DML", 1, &api).
struct OrtDmlApi {
  ORT_API2_STATUS(SessionOptionsAppendExecutionProvider_DML,
                  _In_ OrtSessionOptions* options, int device_id);
  ORT_API2_STATUS(SessionOptionsAppendExecutionProvider_DML1,
                  _In_ OrtSessionOptions* options, _In_ IDMLDevice* dml_device,
                  _In_ ID3D12CommandQueue* cmd_queue);
  ORT_API2_STATUS(CreateGPUAllocationFromD3DResource,
                  _In_ ID3D12Resource* d3d_resource, _Out_ void** dml_resource);
  ORT_API2_STATUS(FreeGPUAllocation, _In_ void* dml_resource);
  ORT_API2_STATUS(GetD3D12ResourceFromAllocation, _In_ OrtAllocator* provider,
                  _In_ void* dml_resource, _Out_ ID3D12Resource** d3d_resource);
  ORT_API2_STATUS(SessionOptionsAppendExecutionProvider_DML2,
                  _In_ OrtSessionOptions* options, OrtDmlDeviceOptions* device_opts);
  ORT_API2_STATUS(GetDMLDevice, _In_ OrtSessionOptions* options,
                  _Out_ IDMLDevice** dmlDevice);
  ORT_API2_STATUS(GetDMLCommandQueue, _In_ OrtSessionOptions* options,
                  _Out_ ID3D12CommandQueue** dmlCommandQueue);
};

#ifdef __cplusplus
}
#endif

#endif  // ORT_DML_CAPI_H
