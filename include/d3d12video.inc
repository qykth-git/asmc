ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __d3d12video_h__
__d3d12video_h__ equ <>

ifndef __ID3D12VideoDecoderHeap_FWD_DEFINED__
__ID3D12VideoDecoderHeap_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoDevice_FWD_DEFINED__
__ID3D12VideoDevice_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoDecoder_FWD_DEFINED__
__ID3D12VideoDecoder_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoProcessor_FWD_DEFINED__
__ID3D12VideoProcessor_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoDecodeCommandList_FWD_DEFINED__
__ID3D12VideoDecodeCommandList_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoProcessCommandList_FWD_DEFINED__
__ID3D12VideoProcessCommandList_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoDecodeCommandList1_FWD_DEFINED__
__ID3D12VideoDecodeCommandList1_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoProcessCommandList1_FWD_DEFINED__
__ID3D12VideoProcessCommandList1_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoMotionEstimator_FWD_DEFINED__
__ID3D12VideoMotionEstimator_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoMotionVectorHeap_FWD_DEFINED__
__ID3D12VideoMotionVectorHeap_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoDevice1_FWD_DEFINED__
__ID3D12VideoDevice1_FWD_DEFINED__ equ 1
endif
ifndef __ID3D12VideoEncodeCommandList_FWD_DEFINED__
__ID3D12VideoEncodeCommandList_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc
include dxgicommon.inc
include d3d12.inc

.enum D3D12_VIDEO_FIELD_TYPE {
    D3D12_VIDEO_FIELD_TYPE_NONE = 0,
    D3D12_VIDEO_FIELD_TYPE_INTERLACED_TOP_FIELD_FIRST	= 1,
    D3D12_VIDEO_FIELD_TYPE_INTERLACED_BOTTOM_FIELD_FIRST	= 2
    }

.enum D3D12_VIDEO_FRAME_STEREO_FORMAT {
    D3D12_VIDEO_FRAME_STEREO_FORMAT_NONE	= 0,
    D3D12_VIDEO_FRAME_STEREO_FORMAT_MONO	= 1,
    D3D12_VIDEO_FRAME_STEREO_FORMAT_HORIZONTAL	= 2,
    D3D12_VIDEO_FRAME_STEREO_FORMAT_VERTICAL	= 3,
    D3D12_VIDEO_FRAME_STEREO_FORMAT_SEPARATE	= 4
    }

D3D12_VIDEO_FORMAT	STRUC
Format			DXGI_FORMAT ?
ColorSpace		DXGI_COLOR_SPACE_TYPE ?
D3D12_VIDEO_FORMAT	ENDS

D3D12_VIDEO_SAMPLE	STRUC
Width			UINT ?
Height			UINT ?
Format			D3D12_VIDEO_FORMAT <>
D3D12_VIDEO_SAMPLE	ENDS

.enum D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE {
    D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE_NONE = 0,
    D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE_FIELD_BASED	= 1
    }

.enum D3D12_FEATURE_VIDEO {
    D3D12_FEATURE_VIDEO_DECODE_SUPPORT	= 0,
    D3D12_FEATURE_VIDEO_DECODE_PROFILES = 1,
    D3D12_FEATURE_VIDEO_DECODE_FORMATS	= 2,
    D3D12_FEATURE_VIDEO_DECODE_CONVERSION_SUPPORT	= 3,
    D3D12_FEATURE_VIDEO_PROCESS_SUPPORT = 5,
    D3D12_FEATURE_VIDEO_PROCESS_MAX_INPUT_STREAMS	= 6,
    D3D12_FEATURE_VIDEO_PROCESS_REFERENCE_INFO	= 7,
    D3D12_FEATURE_VIDEO_DECODER_HEAP_SIZE	= 8,
    D3D12_FEATURE_VIDEO_PROCESSOR_SIZE	= 9,
    D3D12_FEATURE_VIDEO_DECODE_PROFILE_COUNT	= 10,
    D3D12_FEATURE_VIDEO_DECODE_FORMAT_COUNT	= 11,
    D3D12_FEATURE_VIDEO_ARCHITECTURE	= 17,
    D3D12_FEATURE_VIDEO_DECODE_HISTOGRAM	= 18,
    D3D12_FEATURE_VIDEO_FEATURE_AREA_SUPPORT	= 19,
    D3D12_FEATURE_VIDEO_MOTION_ESTIMATOR	= 20,
    D3D12_FEATURE_VIDEO_MOTION_ESTIMATOR_SIZE	= 21
    }

.enum D3D12_BITSTREAM_ENCRYPTION_TYPE {
    D3D12_BITSTREAM_ENCRYPTION_TYPE_NONE	= 0
    }

D3D12_VIDEO_DECODE_CONFIGURATION STRUC
DecodeProfile		GUID <>
BitstreamEncryption	D3D12_BITSTREAM_ENCRYPTION_TYPE ?
InterlaceType		D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE ?
D3D12_VIDEO_DECODE_CONFIGURATION ENDS

D3D12_VIDEO_DECODER_DESC STRUC
NodeMask		UINT ?
Configuration		D3D12_VIDEO_DECODE_CONFIGURATION <>
D3D12_VIDEO_DECODER_DESC ENDS

D3D12_VIDEO_DECODER_HEAP_DESC STRUC
NodeMask		UINT ?
Configuration		D3D12_VIDEO_DECODE_CONFIGURATION <>
DecodeWidth		UINT ?
DecodeHeight		UINT ?
Format			DXGI_FORMAT ?
FrameRate		DXGI_RATIONAL <>
BitRate			UINT ?
MaxDecodePictureBufferCount UINT ?
D3D12_VIDEO_DECODER_HEAP_DESC ENDS

D3D12_VIDEO_SIZE_RANGE	STRUC
MaxWidth		UINT ?
MaxHeight		UINT ?
MinWidth		UINT ?
MinHeight		UINT ?
D3D12_VIDEO_SIZE_RANGE	ENDS

.enum D3D12_VIDEO_PROCESS_FILTER {
    D3D12_VIDEO_PROCESS_FILTER_BRIGHTNESS	= 0,
    D3D12_VIDEO_PROCESS_FILTER_CONTRAST = 1,
    D3D12_VIDEO_PROCESS_FILTER_HUE	= 2,
    D3D12_VIDEO_PROCESS_FILTER_SATURATION	= 3,
    D3D12_VIDEO_PROCESS_FILTER_NOISE_REDUCTION	= 4,
    D3D12_VIDEO_PROCESS_FILTER_EDGE_ENHANCEMENT = 5,
    D3D12_VIDEO_PROCESS_FILTER_ANAMORPHIC_SCALING	= 6,
    D3D12_VIDEO_PROCESS_FILTER_STEREO_ADJUSTMENT	= 7
    }

.enum D3D12_VIDEO_PROCESS_FILTER_FLAGS {
    D3D12_VIDEO_PROCESS_FILTER_FLAG_NONE	= 0,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_BRIGHTNESS		= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_BRIGHTNESS ) ,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_CONTRAST		= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_CONTRAST ) ,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_HUE			= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_HUE ) ,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_SATURATION		= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_SATURATION ) ,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_NOISE_REDUCTION	= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_NOISE_REDUCTION ) ,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_EDGE_ENHANCEMENT	= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_EDGE_ENHANCEMENT ) ,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_ANAMORPHIC_SCALING	= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_ANAMORPHIC_SCALING ) ,
    D3D12_VIDEO_PROCESS_FILTER_FLAG_STEREO_ADJUSTMENT	= ( 1 shl D3D12_VIDEO_PROCESS_FILTER_STEREO_ADJUSTMENT )
    }

.enum D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS {
    D3D12_VIDEO_PROCESS_DEINTERLACE_FLAG_NONE	= 0,
    D3D12_VIDEO_PROCESS_DEINTERLACE_FLAG_BOB	= 0x1,
    D3D12_VIDEO_PROCESS_DEINTERLACE_FLAG_CUSTOM = 0x80000000
    }

D3D12_VIDEO_PROCESS_ALPHA_BLENDING STRUC
Enable			BOOL ?
Alpha			FLOAT ?
D3D12_VIDEO_PROCESS_ALPHA_BLENDING ENDS

D3D12_VIDEO_PROCESS_LUMA_KEY STRUC
Enable			BOOL ?
Lower			FLOAT ?
Upper			FLOAT ?
D3D12_VIDEO_PROCESS_LUMA_KEY ENDS

D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC STRUC
Format			DXGI_FORMAT ?
ColorSpace		DXGI_COLOR_SPACE_TYPE ?
SourceAspectRatio	DXGI_RATIONAL <>
DestinationAspectRatio	DXGI_RATIONAL <>
FrameRate		DXGI_RATIONAL <>
SourceSizeRange		D3D12_VIDEO_SIZE_RANGE <>
DestinationSizeRange	D3D12_VIDEO_SIZE_RANGE <>
EnableOrientation	BOOL ?
FilterFlags		D3D12_VIDEO_PROCESS_FILTER_FLAGS ?
StereoFormat		D3D12_VIDEO_FRAME_STEREO_FORMAT ?
FieldType		D3D12_VIDEO_FIELD_TYPE ?
DeinterlaceMode		D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS ?
EnableAlphaBlending	BOOL ?
LumaKey			D3D12_VIDEO_PROCESS_LUMA_KEY <>
NumPastFrames		UINT ?
NumFutureFrames		UINT ?
EnableAutoProcessing	BOOL ?
D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC ENDS

.enum D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE {
    D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_OPAQUE	= 0,
    D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_BACKGROUND	= 1,
    D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_DESTINATION	= 2,
    D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_SOURCE_STREAM	= 3
    }

D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC STRUC
Format			DXGI_FORMAT ?
ColorSpace		DXGI_COLOR_SPACE_TYPE ?
AlphaFillMode		D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE ?
AlphaFillModeSourceStreamIndex UINT ?
BackgroundColor		FLOAT  4  dup(?)
FrameRate		DXGI_RATIONAL <>
EnableStereo		BOOL ?
D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC ENDS

ifndef __ID3D12VideoDecoderHeap_INTERFACE_DEFINED__
__ID3D12VideoDecoderHeap_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoDecoderHeap : public ID3D12Pageable

    GetDesc		proc
    .ends

endif

ifndef __ID3D12VideoDevice_INTERFACE_DEFINED__
__ID3D12VideoDevice_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoDevice : public IUnknown

    CheckFeatureSupport proc :D3D12_FEATURE_VIDEO
    CreateVideoDecoder	proc :ptr, :REFIID, :ptr
    CreateVideoDecoderHeap proc :ptr, :REFIID, :ptr
    CreateVideoProcessor proc :UINT, :ptr, :UINT
    .ends

endif

ifndef __ID3D12VideoDecoder_INTERFACE_DEFINED__
__ID3D12VideoDecoder_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoDecoder : public ID3D12Pageable

    GetDesc		proc
    .ends

endif

.enum D3D12_VIDEO_DECODE_TIER {
    D3D12_VIDEO_DECODE_TIER_NOT_SUPPORTED	= 0,
    D3D12_VIDEO_DECODE_TIER_1	= 1,
    D3D12_VIDEO_DECODE_TIER_2	= 2,
    D3D12_VIDEO_DECODE_TIER_3	= 3
    }

.enum D3D12_VIDEO_DECODE_SUPPORT_FLAGS {
    D3D12_VIDEO_DECODE_SUPPORT_FLAG_NONE	= 0,
    D3D12_VIDEO_DECODE_SUPPORT_FLAG_SUPPORTED	= 0x1
    }

.enum D3D12_VIDEO_DECODE_CONFIGURATION_FLAGS {
    D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_NONE	= 0,
    D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_HEIGHT_ALIGNMENT_MULTIPLE_32_REQUIRED = 0x1,
    D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_POST_PROCESSING_SUPPORTED	= 0x2,
    D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_REFERENCE_ONLY_ALLOCATIONS_REQUIRED	= 0x4,
    D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_ALLOW_RESOLUTION_CHANGE_ON_NON_KEY_FRAME	= 0x8
    }

.enum D3D12_VIDEO_DECODE_STATUS {
    D3D12_VIDEO_DECODE_STATUS_OK	= 0,
    D3D12_VIDEO_DECODE_STATUS_CONTINUE	= 1,
    D3D12_VIDEO_DECODE_STATUS_CONTINUE_SKIP_DISPLAY	= 2,
    D3D12_VIDEO_DECODE_STATUS_RESTART	= 3
    }

.enum D3D12_VIDEO_DECODE_ARGUMENT_TYPE {
    D3D12_VIDEO_DECODE_ARGUMENT_TYPE_PICTURE_PARAMETERS = 0,
    D3D12_VIDEO_DECODE_ARGUMENT_TYPE_INVERSE_QUANTIZATION_MATRIX	= 1,
    D3D12_VIDEO_DECODE_ARGUMENT_TYPE_SLICE_CONTROL	= 2,
    D3D12_VIDEO_DECODE_ARGUMENT_TYPE_MAX_VALID	= 3
    }

D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT STRUC
NodeIndex		UINT ?
Configuration		D3D12_VIDEO_DECODE_CONFIGURATION <>
Width			UINT ?
Height			UINT ?
DecodeFormat		DXGI_FORMAT ?
FrameRate		DXGI_RATIONAL <>
BitRate			UINT ?
SupportFlags		D3D12_VIDEO_DECODE_SUPPORT_FLAGS ?
ConfigurationFlags	D3D12_VIDEO_DECODE_CONFIGURATION_FLAGS ?
DecodeTier		D3D12_VIDEO_DECODE_TIER ?
D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT ENDS

D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILE_COUNT STRUC
NodeIndex		UINT ?
ProfileCount		UINT ?
D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILE_COUNT ENDS

D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILES STRUC
NodeIndex		UINT ?
ProfileCount		UINT ?
pProfiles		LPGUID ?
D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILES ENDS

D3D12_FEATURE_DATA_VIDEO_DECODE_FORMAT_COUNT STRUC
NodeIndex		UINT ?
Configuration		D3D12_VIDEO_DECODE_CONFIGURATION <>
FormatCount		UINT ?
D3D12_FEATURE_DATA_VIDEO_DECODE_FORMAT_COUNT ENDS

D3D12_FEATURE_DATA_VIDEO_DECODE_FORMATS STRUC
NodeIndex		UINT ?
Configuration		D3D12_VIDEO_DECODE_CONFIGURATION <>
FormatCount		UINT ?
pOutputFormats		PVOID ? ; DXGI_FORMAT *
D3D12_FEATURE_DATA_VIDEO_DECODE_FORMATS ENDS

D3D12_FEATURE_DATA_VIDEO_ARCHITECTURE STRUC
IOCoherent		BOOL ?
D3D12_FEATURE_DATA_VIDEO_ARCHITECTURE ENDS

.enum D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT {
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_Y	= 0,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_U	= 1,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_V	= 2,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_R	= 0,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_G	= 1,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_B	= 2,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_A	= 3
    }

.enum D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAGS {
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_NONE	= 0,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_Y	= ( 1 shl D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_Y ) ,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_U	= ( 1 shl D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_U ) ,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_V	= ( 1 shl D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_V ) ,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_R	= ( 1 shl D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_R ) ,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_G	= ( 1 shl D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_G ) ,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_B	= ( 1 shl D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_B ) ,
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_A	= ( 1 shl D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_A )
    }

D3D12_FEATURE_DATA_VIDEO_DECODE_HISTOGRAM STRUC
NodeIndex		UINT ?
DecodeProfile		GUID <>
Width			UINT ?
Height			UINT ?
DecodeFormat		DXGI_FORMAT ?
Components		D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAGS ?
BinCount		UINT ?
CounterBitDepth		UINT ?
D3D12_FEATURE_DATA_VIDEO_DECODE_HISTOGRAM ENDS

.enum D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAGS {
    D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAG_NONE	= 0,
    D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAG_SUPPORTED	= 0x1
    }

.enum D3D12_VIDEO_SCALE_SUPPORT_FLAGS {
    D3D12_VIDEO_SCALE_SUPPORT_FLAG_NONE = 0,
    D3D12_VIDEO_SCALE_SUPPORT_FLAG_POW2_ONLY	= 0x1,
    D3D12_VIDEO_SCALE_SUPPORT_FLAG_EVEN_DIMENSIONS_ONLY = 0x2
    }

D3D12_VIDEO_SCALE_SUPPORT STRUC
OutputSizeRange		D3D12_VIDEO_SIZE_RANGE <>
Flags			D3D12_VIDEO_SCALE_SUPPORT_FLAGS ?
D3D12_VIDEO_SCALE_SUPPORT ENDS

D3D12_FEATURE_DATA_VIDEO_DECODE_CONVERSION_SUPPORT STRUC
NodeIndex		UINT ?
Configuration		D3D12_VIDEO_DECODE_CONFIGURATION <>
DecodeSample		D3D12_VIDEO_SAMPLE <>
OutputFormat		D3D12_VIDEO_FORMAT <>
FrameRate		DXGI_RATIONAL <>
BitRate			UINT ?
SupportFlags		D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAGS ?
ScaleSupport		D3D12_VIDEO_SCALE_SUPPORT <>
D3D12_FEATURE_DATA_VIDEO_DECODE_CONVERSION_SUPPORT ENDS

D3D12_FEATURE_DATA_VIDEO_DECODER_HEAP_SIZE STRUC
VideoDecoderHeapDesc	D3D12_VIDEO_DECODER_HEAP_DESC <>
MemoryPoolL0Size	UINT64 ?
MemoryPoolL1Size	UINT64 ?
D3D12_FEATURE_DATA_VIDEO_DECODER_HEAP_SIZE ENDS

D3D12_FEATURE_DATA_VIDEO_PROCESSOR_SIZE STRUC
NodeMask		UINT ?
pOutputStreamDesc	PVOID ? ; LPD3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC
NumInputStreamDescs	UINT ?
pInputStreamDescs	PVOID ? ; LPD3D12_VIDEO_PROCESS_INPUT_STREAM_DESC
MemoryPoolL0Size	UINT64 ?
MemoryPoolL1Size	UINT64 ?
D3D12_FEATURE_DATA_VIDEO_PROCESSOR_SIZE ENDS

D3D12_QUERY_DATA_VIDEO_DECODE_STATISTICS STRUC
Status			UINT64 ?
NumMacroblocksAffected	UINT64 ?
FrameRate		DXGI_RATIONAL <>
BitRate			UINT ?
D3D12_QUERY_DATA_VIDEO_DECODE_STATISTICS ENDS

D3D12_VIDEO_DECODE_SUB_SAMPLE_MAPPING_BLOCK STRUC
ClearSize		UINT ?
EncryptedSize		UINT ?
D3D12_VIDEO_DECODE_SUB_SAMPLE_MAPPING_BLOCK ENDS

D3D12_VIDEO_DECODE_FRAME_ARGUMENT STRUC
Type			D3D12_VIDEO_DECODE_ARGUMENT_TYPE ?
Size			UINT ?
pData			PVOID ?
D3D12_VIDEO_DECODE_FRAME_ARGUMENT ENDS

D3D12_VIDEO_DECODE_REFERENCE_FRAMES STRUC
NumTexture2Ds		UINT ?
ppTexture2Ds		PVOID ? ; ID3D12Resource **
pSubresources		LPUINT ?
ppHeaps			PVOID ? ; ID3D12VideoDecoderHeap **
D3D12_VIDEO_DECODE_REFERENCE_FRAMES ENDS

D3D12_VIDEO_DECODE_COMPRESSED_BITSTREAM STRUC
pBuffer			LPID3D12Resource ?
Offs			UINT64 ?
Size			UINT64 ?
D3D12_VIDEO_DECODE_COMPRESSED_BITSTREAM ENDS

D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS STRUC
Enable			BOOL ?
pReferenceTexture2D	LPID3D12Resource ?
ReferenceSubresource	UINT ?
OutputColorSpace	DXGI_COLOR_SPACE_TYPE ?
DecodeColorSpace	DXGI_COLOR_SPACE_TYPE ?
D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS ENDS

D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS STRUC
NumFrameArguments	UINT ?
FrameArguments		D3D12_VIDEO_DECODE_FRAME_ARGUMENT 10 dup(<>)
ReferenceFrames		D3D12_VIDEO_DECODE_REFERENCE_FRAMES <>
CompressedBitstream	D3D12_VIDEO_DECODE_COMPRESSED_BITSTREAM <>
pHeap			PVOID ? ; LPID3D12VideoDecoderHeap
D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS ENDS

D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS STRUC
pOutputTexture2D	LPID3D12Resource ?
OutputSubresource	UINT ?
ConversionArguments	D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS <>
D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS ENDS

ifndef __ID3D12VideoProcessor_INTERFACE_DEFINED__
__ID3D12VideoProcessor_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoProcessor : public ID3D12Pageable

    GetNodeMask		proc
    GetNumInputStreamDescs proc
    GetInputStreamDescs proc :UINT, :ptr
    GetOutputStreamDesc proc
    .ends

endif

.enum D3D12_VIDEO_PROCESS_FEATURE_FLAGS {
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_NONE	= 0,
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_ALPHA_FILL = 0x1,
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_LUMA_KEY	= 0x2,
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_STEREO	= 0x4,
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_ROTATION	= 0x8,
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_FLIP	= 0x10,
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_ALPHA_BLENDING	= 0x20,
    D3D12_VIDEO_PROCESS_FEATURE_FLAG_PIXEL_ASPECT_RATIO = 0x40
    }

.enum D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAGS {
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_NONE	= 0,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_DENOISE	= 0x1,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_DERINGING	= 0x2,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_EDGE_ENHANCEMENT	= 0x4,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_COLOR_CORRECTION	= 0x8,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_FLESH_TONE_MAPPING = 0x10,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_IMAGE_STABILIZATION	= 0x20,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_SUPER_RESOLUTION	= 0x40,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_ANAMORPHIC_SCALING = 0x80,
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_CUSTOM	= 0x80000000
    }

.enum D3D12_VIDEO_PROCESS_ORIENTATION {
    D3D12_VIDEO_PROCESS_ORIENTATION_DEFAULT	= 0,
    D3D12_VIDEO_PROCESS_ORIENTATION_FLIP_HORIZONTAL	= 1,
    D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_90	= 2,
    D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_90_FLIP_HORIZONTAL	= 3,
    D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_180	= 4,
    D3D12_VIDEO_PROCESS_ORIENTATION_FLIP_VERTICAL	= 5,
    D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_270	= 6,
    D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_270_FLIP_HORIZONTAL	= 7
    }

.enum D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS {
    D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAG_NONE	= 0,
    D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAG_FRAME_DISCONTINUITY	= 0x1,
    D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAG_FRAME_REPEAT	= 0x2
    }

D3D12_VIDEO_PROCESS_FILTER_RANGE STRUC
Minimum			int_t ?
Maximum			int_t ?
Default			int_t ?
Multiplier		FLOAT ?
D3D12_VIDEO_PROCESS_FILTER_RANGE ENDS

.enum D3D12_VIDEO_PROCESS_SUPPORT_FLAGS {
    D3D12_VIDEO_PROCESS_SUPPORT_FLAG_NONE	= 0,
    D3D12_VIDEO_PROCESS_SUPPORT_FLAG_SUPPORTED	= 0x1
    }

D3D12_FEATURE_DATA_VIDEO_PROCESS_SUPPORT STRUC
NodeIndex		UINT ?
InputSample		D3D12_VIDEO_SAMPLE <>
InputFieldType		D3D12_VIDEO_FIELD_TYPE ?
InputStereoFormat	D3D12_VIDEO_FRAME_STEREO_FORMAT ?
InputFrameRate		DXGI_RATIONAL <>
OutputFormat		D3D12_VIDEO_FORMAT <>
OutputStereoFormat	D3D12_VIDEO_FRAME_STEREO_FORMAT ?
OutputFrameRate		DXGI_RATIONAL <>
SupportFlags		D3D12_VIDEO_PROCESS_SUPPORT_FLAGS ?
ScaleSupport		D3D12_VIDEO_SCALE_SUPPORT <>
FeatureSupport		D3D12_VIDEO_PROCESS_FEATURE_FLAGS ?
DeinterlaceSupport	D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS ?
AutoProcessingSupport	D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAGS ?
FilterSupport		D3D12_VIDEO_PROCESS_FILTER_FLAGS ?
FilterRangeSupport	D3D12_VIDEO_PROCESS_FILTER_RANGE 32 dup(<>)
D3D12_FEATURE_DATA_VIDEO_PROCESS_SUPPORT ENDS

D3D12_FEATURE_DATA_VIDEO_PROCESS_MAX_INPUT_STREAMS STRUC
NodeIndex		UINT ?
MaxInputStreams		UINT ?
D3D12_FEATURE_DATA_VIDEO_PROCESS_MAX_INPUT_STREAMS ENDS

D3D12_FEATURE_DATA_VIDEO_PROCESS_REFERENCE_INFO STRUC
NodeIndex		UINT ?
DeinterlaceMode		D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS ?
Filters			D3D12_VIDEO_PROCESS_FILTER_FLAGS ?
FeatureSupport		D3D12_VIDEO_PROCESS_FEATURE_FLAGS ?
InputFrameRate		DXGI_RATIONAL <>
OutputFrameRate		DXGI_RATIONAL <>
EnableAutoProcessing	BOOL ?
PastFrames		UINT ?
FutureFrames		UINT ?
D3D12_FEATURE_DATA_VIDEO_PROCESS_REFERENCE_INFO ENDS

D3D12_VIDEO_PROCESS_REFERENCE_SET STRUC
NumPastFrames		UINT ?
ppPastFrames		LPID3D12Resource ?
pPastSubresources	LPUINT ?
NumFutureFrames		UINT ?
ppFutureFrames		LPID3D12Resource ?
pFutureSubresources	LPUINT ?
D3D12_VIDEO_PROCESS_REFERENCE_SET ENDS

D3D12_VIDEO_PROCESS_TRANSFORM STRUC
SourceRectangle		D3D12_RECT <>
DestinationRectangle	D3D12_RECT <>
Orientation		D3D12_VIDEO_PROCESS_ORIENTATION ?
D3D12_VIDEO_PROCESS_TRANSFORM ENDS

D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE STRUC
OutputIndex		UINT ?
InputFrameOrField	UINT ?
D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE ENDS

D3D12_VIDEO_PROCESS_INPUT_STREAM STRUC
pTexture2D		LPID3D12Resource ?
Subresource		UINT ?
ReferenceSet		D3D12_VIDEO_PROCESS_REFERENCE_SET <>
D3D12_VIDEO_PROCESS_INPUT_STREAM ENDS

D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS STRUC
InputStream		D3D12_VIDEO_PROCESS_INPUT_STREAM 2 dup(<>)
Transform		D3D12_VIDEO_PROCESS_TRANSFORM <>
Flags			D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS ?
RateInfo		D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE <>
FilterLevels		int_t  32  dup(?)
AlphaBlending		D3D12_VIDEO_PROCESS_ALPHA_BLENDING <>
D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS ENDS

D3D12_VIDEO_PROCESS_OUTPUT_STREAM STRUC
pTexture2D		LPID3D12Resource ?
Subresource		UINT ?
D3D12_VIDEO_PROCESS_OUTPUT_STREAM ENDS

D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS STRUC
OutputStream		D3D12_VIDEO_PROCESS_OUTPUT_STREAM 2 dup(<>)
TargetRectangle		D3D12_RECT <>
D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS ENDS

ifndef __ID3D12VideoDecodeCommandList_INTERFACE_DEFINED__
__ID3D12VideoDecodeCommandList_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoDecodeCommandList : public ID3D12CommandList

    Close		proc
    Reset		proc :ptr
    ClearState		proc
    ResourceBarrier	proc :UINT, :ptr
    DiscardResource	proc :ptr, :ptr
    BeginQuery		proc :ptr, :D3D12_QUERY_TYPE, :UINT
    EndQuery		proc :ptr, :D3D12_QUERY_TYPE, :UINT
    ResolveQueryData	proc :ptr, :D3D12_QUERY_TYPE, :UINT, :UINT, :ptr, :UINT64
    SetPredication	proc :ptr, :UINT64, :D3D12_PREDICATION_OP
    SetMarker		proc :UINT
    BeginEvent		proc :UINT
    EndEvent		proc
    DecodeFrame		proc :ptr, :ptr, :ptr
    WriteBufferImmediate proc :UINT, :ptr
    .ends

endif


ifndef __ID3D12VideoProcessCommandList_INTERFACE_DEFINED__
__ID3D12VideoProcessCommandList_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoProcessCommandList : public ID3D12CommandList

    Close		proc
    Reset		proc :ptr
    ClearState		proc
    ResourceBarrier	proc :UINT, :ptr
    DiscardResource	proc :ptr, :ptr
    BeginQuery		proc :ptr, :D3D12_QUERY_TYPE, :UINT
    EndQuery		proc :ptr, :D3D12_QUERY_TYPE, :UINT
    ResolveQueryData	proc :ptr, :D3D12_QUERY_TYPE, :UINT, :UINT, :ptr, :UINT64
    SetPredication	proc :ptr, :UINT64, :D3D12_PREDICATION_OP
    SetMarker		proc :UINT
    BeginEvent		proc :UINT
    EndEvent		proc
    ProcessFrames	proc :ptr, :ptr, :UINT, :ptr
    WriteBufferImmediate proc :UINT, :ptr
    .ends

endif

D3D12_VIDEO_DECODE_OUTPUT_HISTOGRAM STRUC
Offs			UINT64 ?
pBuffer			LPID3D12Resource ?
D3D12_VIDEO_DECODE_OUTPUT_HISTOGRAM ENDS

D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS1 STRUC
Enable			BOOL ?
pReferenceTexture2D	LPID3D12Resource ?
ReferenceSubresource	UINT ?
OutputColorSpace	DXGI_COLOR_SPACE_TYPE ?
DecodeColorSpace	DXGI_COLOR_SPACE_TYPE ?
OutputWidth		UINT ?
OutputHeight		UINT ?
D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS1 ENDS

D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 STRUC
pOutputTexture2D	LPID3D12Resource ?
OutputSubresource	UINT ?
ConversionArguments	D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS1 <>
Histograms		D3D12_VIDEO_DECODE_OUTPUT_HISTOGRAM 4 dup(<>)
D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 ENDS

ifndef __ID3D12VideoDecodeCommandList1_INTERFACE_DEFINED__
__ID3D12VideoDecodeCommandList1_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoDecodeCommandList1 : public ID3D12VideoDecodeCommandList

    DecodeFrame1	proc :ptr, :ptr, :ptr
    .ends

endif


D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1 STRUC
InputStream		D3D12_VIDEO_PROCESS_INPUT_STREAM 2 dup(<>)
Transform		D3D12_VIDEO_PROCESS_TRANSFORM <>
Flags			D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS ?
RateInfo		D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE <>
FilterLevels		int_t  32  dup(?)
AlphaBlending		D3D12_VIDEO_PROCESS_ALPHA_BLENDING <>
FieldType		D3D12_VIDEO_FIELD_TYPE ?
D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1 ENDS

ifndef __ID3D12VideoProcessCommandList1_INTERFACE_DEFINED__
__ID3D12VideoProcessCommandList1_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoProcessCommandList1 : public ID3D12VideoProcessCommandList

    ProcessFrames1	proc :ptr, :ptr, :UINT, :ptr
    .ends

endif

.enum D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE {
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_8X8	= 0,
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_16X16	= 1
    }

.enum D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAGS {
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAG_NONE	= 0,
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAG_8X8	= ( 1 shl D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_8X8 ) ,
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAG_16X16	= ( 1 shl D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_16X16 )
    }

.enum D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION {
    D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_QUARTER_PEL	= 0
    }

.enum D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAGS {
    D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAG_NONE	= 0,
    D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAG_QUARTER_PEL = ( 1 shl D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_QUARTER_PEL )
    }

D3D12_FEATURE_DATA_VIDEO_FEATURE_AREA_SUPPORT STRUC
NodeIndex		UINT ?
VideoDecodeSupport	BOOL ?
VideoProcessSupport	BOOL ?
VideoEncodeSupport	BOOL ?
D3D12_FEATURE_DATA_VIDEO_FEATURE_AREA_SUPPORT ENDS

D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR STRUC
NodeIndex		UINT ?
InputFormat		DXGI_FORMAT ?
BlockSizeFlags		D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAGS ?
PrecisionFlags		D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAGS ?
SizeRange		D3D12_VIDEO_SIZE_RANGE <>
D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR ENDS

D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR_SIZE STRUC
NodeIndex		UINT ?
InputFormat		DXGI_FORMAT ?
BlockSize		D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE ?
Precision		D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION ?
SizeRange		D3D12_VIDEO_SIZE_RANGE <>
Protected		BOOL ?
MotionVectorHeapMemoryPoolL0Size UINT64 ?
MotionVectorHeapMemoryPoolL1Size UINT64 ?
MotionEstimatorMemoryPoolL0Size UINT64 ?
MotionEstimatorMemoryPoolL1Size UINT64 ?
D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR_SIZE ENDS

D3D12_VIDEO_MOTION_ESTIMATOR_DESC STRUC
NodeMask		UINT ?
InputFormat		DXGI_FORMAT ?
BlockSize		D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE ?
Precision		D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION ?
SizeRange		D3D12_VIDEO_SIZE_RANGE <>
D3D12_VIDEO_MOTION_ESTIMATOR_DESC ENDS

ifndef __ID3D12VideoMotionEstimator_INTERFACE_DEFINED__
__ID3D12VideoMotionEstimator_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoMotionEstimator : public ID3D12Pageable

    GetDesc		proc
    GetProtectedResourceSession proc :REFIID, :ptr
    .ends

endif

D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC STRUC
NodeMask		UINT ?
InputFormat		DXGI_FORMAT ?
BlockSize		D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE ?
Precision		D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION ?
SizeRange		D3D12_VIDEO_SIZE_RANGE <>
D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC ENDS

ifndef __ID3D12VideoMotionVectorHeap_INTERFACE_DEFINED__
__ID3D12VideoMotionVectorHeap_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoMotionVectorHeap : public ID3D12Pageable

    GetDesc		proc
    GetProtectedResourceSession proc :REFIID, :ptr
    .ends

endif

ifndef __ID3D12VideoDevice1_INTERFACE_DEFINED__
__ID3D12VideoDevice1_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoDevice1 : public ID3D12VideoDevice

    CreateVideoMotionEstimator proc :ptr, :ptr, :REFIID, :ptr
    CreateVideoMotionVectorHeap proc :ptr, :ptr, :REFIID, :ptr
    .ends

endif

D3D12_RESOURCE_COORDINATE STRUC
X			UINT64 ?
Y			UINT ?
Z			UINT ?
SubresourceIndex	UINT ?
D3D12_RESOURCE_COORDINATE ENDS

D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT STRUC
pMotionVectorHeap	PVOID ? ; LPID3D12VideoMotionVectorHeap
D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT ENDS

D3D12_VIDEO_MOTION_ESTIMATOR_INPUT STRUC
pInputTexture2D		LPID3D12Resource ?
InputSubresourceIndex	UINT ?
pReferenceTexture2D	LPID3D12Resource ?
ReferenceSubresourceIndex UINT ?
pHintMotionVectorHeap	PVOID ? ; LPID3D12VideoMotionVectorHeap
D3D12_VIDEO_MOTION_ESTIMATOR_INPUT ENDS

D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT STRUC
pMotionVectorTexture2D	LPID3D12Resource ?
MotionVectorCoordinate	D3D12_RESOURCE_COORDINATE <>
D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT ENDS

D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT STRUC
pMotionVectorHeap	PVOID ? ; LPID3D12VideoMotionVectorHeap
PixelWidth		UINT ?
PixelHeight		UINT ?
D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT ENDS


ifndef __ID3D12VideoEncodeCommandList_INTERFACE_DEFINED__
__ID3D12VideoEncodeCommandList_INTERFACE_DEFINED__ equ 1

.comdef ID3D12VideoEncodeCommandList : public ID3D12CommandList

    Close		proc
    Reset		proc :ptr
    ClearState		proc
    ResourceBarrier	proc :UINT, :ptr
    DiscardResource	proc :ptr, :ptr
    BeginQuery		proc :ptr, :D3D12_QUERY_TYPE, :UINT
    EndQuery		proc :ptr, :D3D12_QUERY_TYPE, :UINT
    ResolveQueryData	proc :ptr, :D3D12_QUERY_TYPE, :UINT, :UINT, :ptr, :UINT64
    SetPredication	proc :ptr, :UINT64, :D3D12_PREDICATION_OP
    SetMarker		proc :UINT
    BeginEvent		proc :UINT
    EndEvent		proc
    EstimateMotion	proc :ptr, :ptr, :ptr
    ResolveMotionVectorHeap proc :ptr, :ptr
    WriteBufferImmediate proc :UINT, :ptr
    SetProtectedResourceSession proc :ptr
    .ends

endif

DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG2, 0xee27417f, 0x5e28, 0x4e65, 0xbe, 0xea, 0x1d, 0x26, 0xb5, 0x08, 0xad, 0xc9);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG1_AND_MPEG2, 0x86695f12, 0x340e, 0x4f04, 0x9f, 0xd3, 0x92, 0x53, 0xdd, 0x32, 0x74, 0x60);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264, 0x1b81be68, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264_STEREO_PROGRESSIVE, 0xd79be8da, 0x0cf1, 0x4c81, 0xb8, 0x2a, 0x69, 0xa4, 0xe2, 0x36, 0xf4, 0x3d);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264_STEREO, 0xf9aaccbb, 0xc2b6, 0x4cfc, 0x87, 0x79, 0x57, 0x07, 0xb1, 0x76, 0x05, 0x52);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264_MULTIVIEW, 0x705b9d82, 0x76cf, 0x49d6, 0xb7, 0xe6, 0xac, 0x88, 0x72, 0xdb, 0x01, 0x3c);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VC1, 0x1b81beA3, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VC1_D2010, 0x1b81beA4, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG4PT2_SIMPLE, 0xefd64d74, 0xc9e8,0x41d7,0xa5,0xe9,0xe9,0xb0,0xe3,0x9f,0xa3,0x19);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG4PT2_ADVSIMPLE_NOGMC, 0xed418a9f, 0x010d, 0x4eda, 0x9a, 0xe3, 0x9a, 0x65, 0x35, 0x8d, 0x8d, 0x2e);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN, 0x5b11d51b, 0x2f4c, 0x4452, 0xbc, 0xc3, 0x09, 0xf2, 0xa1, 0x16, 0x0c, 0xc0);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10, 0x107af0e0, 0xef1a, 0x4d19, 0xab, 0xa8, 0x67, 0xa1, 0x63, 0x07, 0x3d, 0x13);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VP9, 0x463707f8, 0xa1d0, 0x4585, 0x87, 0x6d, 0x83, 0xaa, 0x6d, 0x60, 0xb8, 0x9e);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VP9_10BIT_PROFILE2, 0xa4c749ef, 0x6ecf, 0x48aa, 0x84, 0x48, 0x50, 0xa7, 0xa1, 0x16, 0x5f, 0xf7);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VP8, 0x90b899ea, 0x3a62, 0x4705, 0x88, 0xb3, 0x8d, 0xf0, 0x4b, 0x27, 0x44, 0xe7);
DEFINE_GUID(IID_ID3D12VideoDecoderHeap,0x0946B7C9,0xEBF6,0x4047,0xBB,0x73,0x86,0x83,0xE2,0x7D,0xBB,0x1F);
DEFINE_GUID(IID_ID3D12VideoDevice,0x1F052807,0x0B46,0x4ACC,0x8A,0x89,0x36,0x4F,0x79,0x37,0x18,0xA4);
DEFINE_GUID(IID_ID3D12VideoDecoder,0xC59B6BDC,0x7720,0x4074,0xA1,0x36,0x17,0xA1,0x56,0x03,0x74,0x70);
DEFINE_GUID(IID_ID3D12VideoProcessor,0x304FDB32,0xBEDE,0x410A,0x85,0x45,0x94,0x3A,0xC6,0xA4,0x61,0x38);
DEFINE_GUID(IID_ID3D12VideoDecodeCommandList,0x3B60536E,0xAD29,0x4E64,0xA2,0x69,0xF8,0x53,0x83,0x7E,0x5E,0x53);
DEFINE_GUID(IID_ID3D12VideoProcessCommandList,0xAEB2543A,0x167F,0x4682,0xAC,0xC8,0xD1,0x59,0xED,0x4A,0x62,0x09);
DEFINE_GUID(IID_ID3D12VideoDecodeCommandList1,0xD52F011B,0xB56E,0x453C,0xA0,0x5A,0xA7,0xF3,0x11,0xC8,0xF4,0x72);
DEFINE_GUID(IID_ID3D12VideoProcessCommandList1,0x542C5C4D,0x7596,0x434F,0x8C,0x93,0x4E,0xFA,0x67,0x66,0xF2,0x67);
DEFINE_GUID(IID_ID3D12VideoMotionEstimator,0x33FDAE0E,0x098B,0x428F,0x87,0xBB,0x34,0xB6,0x95,0xDE,0x08,0xF8);
DEFINE_GUID(IID_ID3D12VideoMotionVectorHeap,0x5BE17987,0x743A,0x4061,0x83,0x4B,0x23,0xD2,0x2D,0xAE,0xA5,0x05);
DEFINE_GUID(IID_ID3D12VideoDevice1,0x981611AD,0xA144,0x4C83,0x98,0x90,0xF3,0x0E,0x26,0xD6,0x58,0xAB);
DEFINE_GUID(IID_ID3D12VideoEncodeCommandList,0x8455293A,0x0CBD,0x4831,0x9B,0x39,0xFB,0xDB,0xAB,0x72,0x47,0x23);

endif