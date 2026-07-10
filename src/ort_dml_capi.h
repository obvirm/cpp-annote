// Minimal DirectML C API declaration for cpp-annote.
// Avoids pulling in the full dml_provider_factory.h (which requires d3d12.h /
// DirectML.h Windows SDK headers). The DML C API is only declared in the
// Windows ORT package's dml_provider_factory.h; we redeclare just the one
// function we use so the build works without the full Windows SDK D3D stack.
#ifndef ORT_DML_CAPI_H
#define ORT_DML_CAPI_H

#include "onnxruntime_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

ORT_API_STATUS(OrtSessionOptionsAppendExecutionProvider_DML,
               _In_ OrtSessionOptions* options, int device_id);

#ifdef __cplusplus
}
#endif

#endif  // ORT_DML_CAPI_H
