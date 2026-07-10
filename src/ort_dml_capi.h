// Minimal DirectML C API declarations for cpp-annote.
//
// Avoids pulling in the real dml_provider_factory.h (which requires the Windows
// SDK d3d12.h / DirectML.h headers). We only need the OrtDmlApi struct so we can
// resolve the DirectML execution provider at *runtime* via
// OrtApi::GetExecutionProviderApi("DML", ...). This means we never statically
// link against onnxruntime_providers_dml.lib (which is absent from the public
// GPU packages), so cpp_annote.dll links cleanly against just onnxruntime.lib.
//
// The D3D12/DML types are forward-declared as opaque pointers — the struct only
// stores function pointers, so their full definitions are never required.
#ifndef ORT_DML_CAPI_H
#define ORT_DML_CAPI_H

#include "onnxruntime_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// Opaque D3D12 / DirectML handles (full defs live in the Windows SDK).
struct IDMLDevice;
typedef struct IDMLDevice IDMLDevice;
struct ID3D12CommandQueue;
typedef struct ID3D12CommandQueue ID3D12CommandQueue;
struct ID3D12Resource;
typedef struct ID3D12Resource ID3D12Resource;

struct OrtDmlDeviceOptions;
typedef struct OrtDmlDeviceOptions OrtDmlDeviceOptions;

// Mirrors the layout of onnxruntime's OrtDmlApi exactly (first member is
// SessionOptionsAppendExecutionProvider_DML). Only the entry we use is called.
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
