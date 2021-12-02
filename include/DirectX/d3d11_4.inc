ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __d3d11_4_h__
define __d3d11_4_h__

include oaidl.inc
include ocidl.inc
include dxgi1_5.inc
include d3dcommon.inc
include d3d11_3.inc

ifndef __ID3D11Device4_INTERFACE_DEFINED__
define __ID3D11Device4_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Device4, "8992ab71-02e6-4b8d-ba48-b056dcda42c4")

.comdef ID3D11Device4 : public ID3D11Device3

    RegisterDeviceRemovedEvent proc :HANDLE, :ptr
    UnregisterDeviceRemoved proc :DWORD
   .ends

endif

ifndef __ID3D11Device5_INTERFACE_DEFINED__
define __ID3D11Device5_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Device5, "8ffde202-a0e7-45df-9e01-e837801b5ea0")

.comdef ID3D11Device5 : public ID3D11Device4

    OpenSharedFence	proc :HANDLE, :REFIID, :ptr
    CreateFence		proc :UINT64, :D3D11_FENCE_FLAG, :REFIID, :ptr
   .ends

endif

ifndef __ID3D11Multithread_INTERFACE_DEFINED__
define __ID3D11Multithread_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Multithread, "9B7E4E00-342C-4106-A19F-4F2704F689F0")

.comdef ID3D11Multithread : public IUnknown

    _Enter		proc
    _Leave		proc
    SetMultithreadProtected proc :BOOL
    GetMultithreadProtected proc
   .ends

endif

ifndef __ID3D11VideoContext2_INTERFACE_DEFINED__
define __ID3D11VideoContext2_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11VideoContext2, "C4E7374C-6243-4D1B-AE87-52B4F740E261")

.comdef ID3D11VideoContext2 : public ID3D11VideoContext1

    VideoProcessorSetOutputHDRMetaData proc :ptr, :DXGI_HDR_METADATA_TYPE, :UINT, :ptr
    VideoProcessorGetOutputHDRMetaData proc :ptr, :ptr, :UINT, :ptr
    VideoProcessorSetStreamHDRMetaData proc :ptr, :UINT, :DXGI_HDR_METADATA_TYPE, :UINT, :ptr
    VideoProcessorGetStreamHDRMetaData proc :ptr, :UINT, :ptr, :UINT, :ptr
   .ends

endif

.enum D3D11_FEATURE_VIDEO {
    D3D11_FEATURE_VIDEO_DECODER_HISTOGRAM	= 0
    }

.enum D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT {
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_Y	= 0,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_U	= 1,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_V	= 2,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_R	= 0,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_G	= 1,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_B	= 2,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_A	= 3
    }

.enum D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAGS {
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_NONE	= 0,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_Y	= ( 1 SHL D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_Y ) ,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_U	= ( 1 SHL D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_U ) ,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_V	= ( 1 SHL D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_V ) ,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_R	= ( 1 SHL D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_R ) ,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_G	= ( 1 SHL D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_G ) ,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_B	= ( 1 SHL D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_B ) ,
    D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_A	= ( 1 SHL D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_A )
    }

D3D11_FEATURE_DATA_VIDEO_DECODER_HISTOGRAM STRUC
DecoderDesc		D3D11_VIDEO_DECODER_DESC <>
Components		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAGS ?
BinCount		UINT ?
CounterBitDepth		UINT ?
D3D11_FEATURE_DATA_VIDEO_DECODER_HISTOGRAM ENDS

.enum D3D11_CRYPTO_SESSION_KEY_EXCHANGE_FLAGS {
    D3D11_CRYPTO_SESSION_KEY_EXCHANGE_FLAG_NONE = 0
    }

ifndef __ID3D11VideoDevice2_INTERFACE_DEFINED__
define __ID3D11VideoDevice2_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11VideoDevice2, "59C0CB01-35F0-4A70-8F67-87905C906A53")

.comdef ID3D11VideoDevice2 : public ID3D11VideoDevice1

    CheckFeatureSupport proc :D3D11_FEATURE_VIDEO
    NegotiateCryptoSessionKeyExchangeMT proc :ptr, :D3D11_CRYPTO_SESSION_KEY_EXCHANGE_FLAGS, :UINT, :ptr
   .ends

endif

D3D11_VIDEO_DECODER_BUFFER_DESC2 STRUC
BufferType		D3D11_VIDEO_DECODER_BUFFER_TYPE ?
DataOffset		UINT ?
DataSize		UINT ?
pIV			PVOID ?
IVSize			UINT ?
pSubSampleMappingBlock	PVOID ? ; D3D11_VIDEO_DECODER_SUB_SAMPLE_MAPPING_BLOCK
SubSampleMappingCount	UINT ?
cBlocksStripeEncrypted	UINT ?
cBlocksStripeClear	UINT ?
D3D11_VIDEO_DECODER_BUFFER_DESC2 ENDS

ifndef __ID3D11VideoContext3_INTERFACE_DEFINED__
define __ID3D11VideoContext3_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11VideoContext3, "A9E2FAA0-CB39-418F-A0B7-D8AAD4DE672E")

.comdef ID3D11VideoContext3 : public ID3D11VideoContext2

    DecoderBeginFrame1	proc :ptr, :ptr, :UINT, :UINT, :ptr
    SubmitDecoderBuffers2 proc :ptr, :UINT, :ptr
   .ends

endif

D3D11_FEATURE_DATA_D3D11_OPTIONS4 STRUC
ExtendedNV12SharedTextureSupported BOOL ?
D3D11_FEATURE_DATA_D3D11_OPTIONS4 ENDS

endif