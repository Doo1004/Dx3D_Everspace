#include "pch.h"
#include "CGraphicsShader.h"

#include "CPathMgr.h"
#include "CDevice.h"

CGraphicsShader::CGraphicsShader()
	: CShader(RES_TYPE::GRAPHICS_SHADER)
	, m_eTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, m_RSType(RS_TYPE::CULL_BACK)
	, m_DSType(DS_TYPE::LESS)
	, m_BSType(BS_TYPE::DEFAULT)
	, m_Domain(SHADER_DOMAIN::DOMAIN_UNDEFINED)
{
}

CGraphicsShader::~CGraphicsShader()
{
}

void CGraphicsShader::CreateVertexShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += _strFileName;

	// VertexShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "vs_5_0", 0, 0, m_VSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Vertex Shader Compile Failed!!", MB_OK);
	}

	// 컴파일된 객체로 VertexShader, PixelShader 를 만든다.
	HRESULT hr = DEVICE->CreateVertexShader(m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, nullptr, m_VS.GetAddressOf());



	// InputLayout 생성
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[8] = {};

	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;
	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;

	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;
	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;

	LayoutDesc[2].SemanticName = "TEXCOORD";
	LayoutDesc[2].SemanticIndex = 0;
	LayoutDesc[2].AlignedByteOffset = 28;
	LayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	LayoutDesc[2].InputSlot = 0;
	LayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[2].InstanceDataStepRate = 0;

	LayoutDesc[3].SemanticName = "TANGENT";
	LayoutDesc[3].SemanticIndex = 0;
	LayoutDesc[3].AlignedByteOffset = 36;
	LayoutDesc[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[3].InputSlot = 0;
	LayoutDesc[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[3].InstanceDataStepRate = 0;

	LayoutDesc[4].SemanticName = "NORMAL";
	LayoutDesc[4].SemanticIndex = 0;
	LayoutDesc[4].AlignedByteOffset = 48;
	LayoutDesc[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[4].InputSlot = 0;
	LayoutDesc[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[4].InstanceDataStepRate = 0;

	LayoutDesc[5].SemanticName = "BINORMAL";
	LayoutDesc[5].SemanticIndex = 0;
	LayoutDesc[5].AlignedByteOffset = 60;
	LayoutDesc[5].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[5].InputSlot = 0;
	LayoutDesc[5].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[5].InstanceDataStepRate = 0;

	LayoutDesc[6].SemanticName = "BLENDWEIGHT";
	LayoutDesc[6].SemanticIndex = 0;
	LayoutDesc[6].AlignedByteOffset = 72;
	LayoutDesc[6].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[6].InputSlot = 0;
	LayoutDesc[6].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[6].InstanceDataStepRate = 0;

	LayoutDesc[7].SemanticName = "BLENDINDICES";
	LayoutDesc[7].SemanticIndex = 0;
	LayoutDesc[7].AlignedByteOffset = 88;
	LayoutDesc[7].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[7].InputSlot = 0;
	LayoutDesc[7].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[7].InstanceDataStepRate = 0;

	hr = DEVICE->CreateInputLayout(LayoutDesc, 8
		, m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, m_Layout.GetAddressOf());

	if (FAILED(hr))
	{
		assert(nullptr);
	}
}

void CGraphicsShader::CreateHullShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += _strFileName;

	// Shader Compile	
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "hs_5_0", 0, 0, m_HSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Shader Compile Failed!!", MB_OK);
	}

	// 컴파일된 객체로 Shader 를 만든다.
	DEVICE->CreateHullShader(m_HSBlob->GetBufferPointer(), m_HSBlob->GetBufferSize()
		, nullptr, m_HS.GetAddressOf());
}

void CGraphicsShader::CreateDomainShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += _strFileName;

	// Shader Compile	
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "ds_5_0", 0, 0, m_DSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Shader Compile Failed!!", MB_OK);
	}

	// 컴파일된 객체로 Shader 를 만든다.
	DEVICE->CreateDomainShader(m_DSBlob->GetBufferPointer(), m_DSBlob->GetBufferSize()
		, nullptr, m_DS.GetAddressOf());
}

void CGraphicsShader::CreateGeometryShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += _strFileName;

	// Shader Compile	
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "gs_5_0", 0, 0, m_GSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Shader Compile Failed!!", MB_OK);
	}

	// 컴파일된 객체로 Shader 를 만든다.
	DEVICE->CreateGeometryShader(m_GSBlob->GetBufferPointer(), m_GSBlob->GetBufferSize()
		, nullptr, m_GS.GetAddressOf());
}

void CGraphicsShader::CreatePixelShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += _strFileName;


	// PixelShader Compile	
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "ps_5_0", 0, 0, m_PSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Pixel Shader Compile Failed!!", MB_OK);
	}

	// 컴파일된 객체로 PixelShader 를 만든다.
	DEVICE->CreatePixelShader(m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize()
		, nullptr, m_PS.GetAddressOf());
}

void CGraphicsShader::UpdateData()
{
	CONTEXT->IASetInputLayout(m_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(m_eTopology);
		
	CONTEXT->VSSetShader(m_VS.Get(), nullptr, 0);
	CONTEXT->HSSetShader(m_HS.Get(), nullptr, 0);
	CONTEXT->DSSetShader(m_DS.Get(), nullptr, 0);
	CONTEXT->GSSetShader(m_GS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(m_PS.Get(), nullptr, 0);

	CONTEXT->RSSetState(CDevice::GetInst()->GetRSState(m_RSType).Get());
	CONTEXT->OMSetDepthStencilState(CDevice::GetInst()->GetDSState(m_DSType).Get(), 10);
	CONTEXT->OMSetBlendState(CDevice::GetInst()->GetBSState(m_BSType).Get(), Vec4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
}
