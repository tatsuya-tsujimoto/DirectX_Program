#include"DirectGraphics.h"


struct XFile
{
	DWORD MaterialNum;
	LPD3DXMESH Meshes;
	LPD3DXBUFFER Materials;
	LPDIRECT3DTEXTURE9* Textures;
};
XFile g_XFile;

LPDIRECT3D9 g_Interface = nullptr;
LPDIRECT3DDEVICE9 g_Device = nullptr;
LPDIRECT3DTEXTURE9 g_Textures[TextureID::TexIDMax];



LPCWSTR g_TextureNameList[] =
{
	TEXT("GHicon.png"),
	TEXT("GHicon.png"),
	TEXT("GHicon.png"),
};


bool InitDirectGraphics(HWND window_handle)
{

	g_Interface = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_Interface == nullptr)
	{
		return false;
	}
	D3DPRESENT_PARAMETERS parameters;

	ZeroMemory(&parameters, sizeof(D3DPRESENT_PARAMETERS));

	parameters.BackBufferCount = 1;

	parameters.BackBufferFormat = D3DFMT_UNKNOWN;

	parameters.Windowed = true;

	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;

	parameters.EnableAutoDepthStencil = TRUE;

	parameters.AutoDepthStencilFormat = D3DFMT_D16;


	HRESULT result = g_Interface->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&parameters,
		&g_Device
	);


	if (FAILED(result))
	{
		return false;
	}

	return true;




}

void ReleaseDirectGraphics()
{
	if (g_Device != nullptr)
	{
		g_Device->Release();
		g_Device = nullptr;
	}

	if (g_Interface != nullptr)
	{
		g_Interface->Release();
		g_Interface = nullptr;
	}

}

void StartDrawing()
{
	g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_Device->Clear(
		0,										// 0�Œ�
		nullptr,								// nullptr
												// D3DCLEAR_ZBUFFER => Z�o�b�t�@���N���A�Ώۂɉ�����
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,		// D3DCLEAR_TARGET�Œ�
		D3DCOLOR_XRGB(255, 0, 0),				// �h��Ԃ��F
		1.0f,									// 1.0f�Œ�
		0										// 0�Œ�
	);

	g_Device->BeginScene();
}

void FinishDrawing()
{
	g_Device->EndScene();
	g_Device->Present(nullptr, nullptr, nullptr, nullptr);

}

void DrawPorigon()
{
	CustomVertex vertices[] =
	{
		{0.0f  ,50.0f ,0.0f,1.0f,0xffffffff},
		{500.0f,300.0f,0.0f,1.0f,0xffffffff},
		{50.0f ,300.0f,0.0f,1.0f,0xffffffff},
	};

	g_Device->SetFVF(FVF_2D_VERTEX);



	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,		// �|���S���̍���
		1,						// �|���S���̐�
		vertices,				// ���_���X�g
		sizeof(CustomVertex)	// �P���_�̃T�C�Y
	);
}

void DrawporigonWithTrinangleList()
{
	CustomVertex vertices[] =
	{
		{0.0f  ,0.0f  ,0.0f,1.0f,0xffff0000},
		{100.0f,0.0f  ,0.0f,1.0f,0xffff0000},
		{0.0f  ,100.0f,0.0f,1.0f,0xff008833},
		{100.0f,0.0f  ,0.0f,1.0f,0xffff0000},
		{100.0f,100.0f,0.0f,1.0f,0xff008833},
		{0.0f  ,100.0f,0.0f,1.0f,0xff008833},
	};
	g_Device->SetFVF(FVF_2D_VERTEX);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,		// �|���S���̍���
		2,						// �|���S���̐�
		vertices,				// ���_���X�g
		sizeof(CustomVertex)	// �P���_�̃T�C�Y
	);
}

void DrawPorigonWithTriangleStrip()
{
	CustomVertex vertices[] =
	{
		{300.0f,0.0f  ,0.0f,1.0f,0xffff0000},
		{350.0f,0.0f  ,0.0f,1.0f,0xffff0000},
		{300.0f,200.0f,0.0f,1.0f,0xffff0000},
		{350.0f,200.0f,0.0f,1.0f,0xffff0000},

	};
	g_Device->SetFVF(FVF_2D_VERTEX);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,	// �|���S���̍���
		2,						// �|���S���̐�
		vertices,				// ���_���X�g
		sizeof(CustomVertex)	// �P���_�̃T�C�Y
	);

}

void DrawPorigonWithTriangleFan(TextureID tex_id)
{
	if (g_Textures[tex_id] == nullptr)
	{
		return;
	}
	CustomVertexTex vertices[] =
	{
		{200.0f,100.0f,0.0f,1.0f,0x90ffffff,0.0f,0.0f},
		{300.0f,100.0f,0.0f,1.0f,0x90ffffff,1.0f,0.0f},
		{300.0f,200.0f,0.0f,1.0f,0x90ffffff,1.0f,1.0f},
		{200.0f,200.0f,0.0f,1.0f,0x90ffffff,0.0f,1.0f},

	};
	g_Device->SetFVF(FVF_2D_VERTEX_TEXTURE);
	g_Device->SetTexture(0, g_Textures[tex_id]);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,		// �|���S���̍���
		2,						// �|���S���̐�
		vertices,				// ���_���X�g
		sizeof(CustomVertexTex)	// �P���_�̃T�C�Y
	);

}




bool LoadTexture(TextureID tex_id)
{
	HRESULT hr = D3DXCreateTextureFromFile(
		g_Device,					// DirectX9�̃f�o�C�X
		g_TextureNameList[tex_id],  // �t�@�C����
		&g_Textures[tex_id]			// �ǂݍ��܂ꂽ�e�N�X�`����񂪕ۑ������ϐ�
	);

	if (FAILED(hr))
	{
		return false;
	}
	return true;

}

void ReleaseTexture()
{
	for (int i = 0; i < TextureID::TexIDMax; i++)
	{
		if (g_Textures[i] != nullptr)
		{
			g_Textures[i] = nullptr;
		}
	}
}


bool LoadXFile(LPCWSTR file_name)
{
	HRESULT hr = D3DXLoadMeshFromX(
		file_name,				
		D3DXMESH_SYSTEMMEM,		
		g_Device,				
		nullptr,				
		&g_XFile.Materials,		
		nullptr,				
		&g_XFile.MaterialNum,	
		&g_XFile.Meshes			
	);
	if (FAILED(hr))
	{
		return false;
	}
	g_XFile.Textures = new LPDIRECT3DTEXTURE9[g_XFile.MaterialNum];
	D3DXMATERIAL* materials = (D3DXMATERIAL*)g_XFile.Materials->GetBufferPointer();

	for (int i = 0; i < g_XFile.MaterialNum; i++)
	{
		if (materials[i].pTextureFilename != nullptr)
		{
			LPSTR char_file_name = materials[i].pTextureFilename;
			wchar_t wtext[256];
			size_t ret;
			mbstowcs_s(&ret, wtext, char_file_name, strlen(char_file_name) + 1);
			LPWSTR file_name = wtext;

			D3DXCreateTextureFromFile(
				g_Device,
				file_name,
				&g_XFile.Textures[i]);
		}
		else
		{
			g_XFile.Textures[i] = nullptr;
		}
	}

	return true;
}




void SetUpView()
{
	D3DXMATRIX matrix;
	D3DXVECTOR3 camera_pos = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	D3DXVECTOR3 eye_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up_vec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(
		&matrix,				// ���ʕۑ��p�s��̐ݒ�
		&camera_pos,			// �J�������W
		&eye_pos,				// �����_���W
		&up_vec					// ���[���h���W��ɂ�����J�����̏�����x�N�g��
	);

	g_Device->SetTransform(D3DTS_VIEW, &matrix);

}
void SetUpProjection()
{

	D3DXMATRIX matrix;				// �v���W�F�N�V��������ۑ����邽�߂̍s��
	float aspect = 640.0f / 480.0f;	// �A�X�y�N�g��i�E�B���h�E�T�C�Y�̉� / �c�j

	D3DXMatrixPerspectiveFovLH(
		&matrix,					 
		D3DXToRadian(60.0f),		
		aspect,						
		0.1f,						
		1000.0f						
	);
	g_Device->SetTransform(D3DTS_PROJECTION, &matrix);
}

void UpdateCamera(float rotate, float go, float slide)
{
	float x = sinf(D3DXToRadian(rotate));
	float z = cosf(D3DXToRadian(rotate));

	x *= -1.0f;
	z *= -1.0f;
	x *= 200;
	z *= 200;

	D3DXMATRIX matrix;
	D3DXVECTOR3 camera_pos = D3DXVECTOR3(go + x, 0.0f, slide + z);
	D3DXVECTOR3 eye_pos = D3DXVECTOR3(go, 0.0f, slide);
	D3DXVECTOR3 up_vec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(
		&matrix,				// ���ʕۑ��p�s��̐ݒ�
		&camera_pos,			// �J�������W
		&eye_pos,				// �����_���W
		&up_vec					// ���[���h���W��ɂ�����J�����̏�����x�N�g��
	);

	g_Device->SetTransform(D3DTS_VIEW, &matrix);

}

void Draw3DPorigon()
{
	g_Device->SetRenderState(D3DRS_LIGHTING, false);

	CustomVertex3D vertices[]
	{
		{-1.0f,-1.0f,0.0f,0xffff0000},
		{0.0f , 1.0f,0.0f,0xffff0000},
		{ 1.0f,-1.0f,0.0f,0xffff0000},
	};



	g_Device->SetFVF(FVF_3D_VERTEX);

	g_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 1, vertices, sizeof(CustomVertex3D));



}



void DrawXFile(float rotate, float go, float slide)
{
	float pos_x = slide;
	float pos_y = 0.0f;
	float pos_z = go;

	float scale_x = 1.0f;
	float scale_y = 1.0f;
	float scale_z = 1.0f;

	float rad_x = D3DXToRadian(0.0f);
	float rad_y = D3DXToRadian(rotate);
	float rad_z = D3DXToRadian(0.0f);

	// �ړ�����
	D3DXMATRIX matrix;
	D3DXMATRIX scale_matrix;
	D3DXMATRIX trans_matrix;
	D3DXMATRIX rotate_x_matrix;
	D3DXMATRIX rotate_y_matrix;
	D3DXMATRIX rotate_z_matrix;

	D3DXMatrixIdentity(&matrix);

	// �g�k
	D3DXMatrixScaling(&scale_matrix, scale_x, scale_y, scale_z);
	// �ړ�
	D3DXMatrixTranslation(&trans_matrix, pos_x, pos_y, pos_z);
	// ��]
	D3DXMatrixRotationX(&rotate_x_matrix, rad_x);
	D3DXMatrixRotationY(&rotate_y_matrix, rad_y);
	D3DXMatrixRotationZ(&rotate_z_matrix, rad_z);


	matrix *= scale_matrix;

	matrix *= rotate_x_matrix;
	matrix *= rotate_y_matrix;
	matrix *= rotate_z_matrix;


	matrix *= trans_matrix;

	g_Device->SetTransform(D3DTS_WORLD, &matrix);


	D3DXMATERIAL* materials = (D3DXMATERIAL*)g_XFile.Materials->GetBufferPointer();
	for (DWORD i = 0; i < g_XFile.MaterialNum; i++)
	{

		g_Device->SetMaterial(&materials[i].MatD3D);
		g_Device->SetTexture(0, g_XFile.Textures[i]);
		g_XFile.Meshes->DrawSubset(i);


	}


}

void ReleaseXFile()
{
	for (int i = 0; i < g_XFile.MaterialNum; i++)
	{
		if (g_XFile.Textures[i] != nullptr)
		{
			g_XFile.Textures[i]->Release();
			g_XFile.Textures[i] = nullptr;
		}
	}


	delete[] g_XFile.Textures;

	if (g_XFile.Materials != nullptr)
	{
		g_XFile.Materials->Release();
		g_XFile.Materials = nullptr;
	}

	if (g_XFile.Meshes != nullptr)
	{
		g_XFile.Meshes->Release();
		g_XFile.Meshes = nullptr;
	}
}


