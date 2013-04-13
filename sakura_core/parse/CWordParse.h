//2007.09.30 kobake CDocLineMgr ���番��
/*
	Copyright (C) 2008, kobake

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

		1. The origin of this software must not be misrepresented;
		   you must not claim that you wrote the original software.
		   If you use this software in a product, an acknowledgment
		   in the product documentation would be appreciated but is
		   not required.

		2. Altered source versions must be plainly marked as such,
		   and must not be misrepresented as being the original software.

		3. This notice may not be removed or altered from any source
		   distribution.
*/
#ifndef SAKURA_CWORDPARSE_6C07A5B6_49DE_430F_A56F_9F2B003214FC9_H_
#define SAKURA_CWORDPARSE_6C07A5B6_49DE_430F_A56F_9F2B003214FC9_H_

#include "basis/SakuraBasis.h"
class CNativeW;

//! ������ގ��ʎq
enum ECharKind{
	CK_NULL,			//!< NULL
	CK_TAB,				//!< �^�u 0x9<=c<=0x9
	CK_CR,				//!< CR = 0x0d 
	CK_LF,				//!< LF = 0x0a 
	CK_CTRL,			//!< ��L�ȊO�� c<0x20

	CK_SPACE,			//!< ���p�̃X�y�[�X 0x20<=c<=0x20
	CK_CSYM,			//!< ���ʎq�Ɏg�p�\�ȕ��� (�p�����A�A���_�[�X�R�A)
	CK_KATA,			//!< ���p�̃J�^�J�i 0xA1<=c<=0xFD
	CK_LATIN,			//!< ���e���P�⏕�A���e���g���̂����A���t�@�x�b�g���̂��� 0x00C0<=c<0x0180
	CK_UDEF,			//!< ���[�U��`�L�[���[�h�����i#$@\�j
	CK_ETC,				//!< ���p�̂��̑�

	CK_ZEN_SPACE,		//!< �S�p�X�y�[�X
	CK_ZEN_NOBASU,		//!< �L�΂��L�� 0x815B<=c<=0x815B '�['
	CK_ZEN_DAKU,		//!< �S�p���_ 0x309B<=c<=0x309C �u�J�K�v
	CK_ZEN_CSYM,		//!< �S�p�ŁA���ʎq�Ɏg�p�\�ȕ��� (�p�����A�A���_�[�X�R�A)

	CK_ZEN_KIGO,		//!< �S�p�̋L��
	CK_HIRA,			//!< �Ђ炪��
	CK_ZEN_KATA,		//!< �S�p�J�^�J�i
	CK_GREEK,			//!< �M���V������
	CK_ZEN_ROS,			//!< ���V�A����:
	CK_ZEN_SKIGO,		//!< �S�p�̓���L��
	CK_ZEN_ETC,			//!< �S�p�̂��̑��i�����Ȃǁj
};

class CWordParse{
public:
	//2001.06.23 N.Nakatani
	//2007.09.30 kobake     CDocLineMgr����ړ�
	/*!
		@brief ���݈ʒu�̒P��͈̔͂𒲂ׂ� static�����o
		@author N.Nakatani
		@retval true	���� ���݈ʒu�̃f�[�^�́u�P��v�ƔF������B
		@retval false	���s ���݈ʒu�̃f�[�^�́u�P��v�Ƃ͌�������Ȃ��C������B
	*/
	static bool WhereCurrentWord_2(
		const wchar_t*	pLine,			//[in]  ���ׂ郁�����S�̂̐擪�A�h���X
		CLogicInt		nLineLen,		//[in]  ���ׂ郁�����S�̗̂L����
		CLogicInt		nIdx,			//[out] �����J�n�n�_:pLine����̑��ΓI�Ȉʒu
		CLogicInt*		pnIdxFrom,		//[out] �P�ꂪ���������ꍇ�́A�P��̐擪�C���f�b�N�X��Ԃ��B
		CLogicInt*		pnIdxTo,		//[out] �P�ꂪ���������ꍇ�́A�P��̏I�[�̎��̃o�C�g�̐擪�C���f�b�N�X��Ԃ��B
		CNativeW*		pcmcmWord,		//[out] �P�ꂪ���������ꍇ�́A���ݒP���؂�o���Ďw�肳�ꂽCMemory�I�u�W�F�N�g�Ɋi�[����B��񂪕s�v�ȏꍇ��NULL���w�肷��B
		CNativeW*		pcmcmWordLeft	//[out] �P�ꂪ���������ꍇ�́A���ݒP��̍��Ɉʒu����P���؂�o���Ďw�肳�ꂽCMemory�I�u�W�F�N�g�Ɋi�[����B��񂪕s�v�ȏꍇ��NULL���w�肷��B
	);

	//! ���݈ʒu�̕����̎�ނ𒲂ׂ�
	static ECharKind WhatKindOfChar(
		const wchar_t*	pData,
		int				pDataLen,
		int				nIdx
	);

	//! ��̕����������������̂̎�ނ𒲂ׂ�
	static ECharKind WhatKindOfTwoChars(
		ECharKind		kindPre,
		ECharKind		kindCur
	);

	//! ��̕����������������̂̎�ނ𒲂ׂ� for �����L�[���[�h
	static ECharKind WhatKindOfTwoChars4KW(
		ECharKind		kindPre,
		ECharKind		kindCur
	);

	//	pLine�i�����FnLineLen�j�̕����񂩂玟�̒P���T���B�T���n�߂�ʒu��nIdx�Ŏw��B
	static bool SearchNextWordPosition(
		const wchar_t*	pLine,
		CLogicInt		nLineLen,
		CLogicInt		nIdx,		//	����
		CLogicInt*		pnColmNew,	//	���������ʒu
		BOOL			bStopsBothEnds	//	�P��̗��[�Ŏ~�܂�
	);

	//	pLine�i�����FnLineLen�j�̕����񂩂玟�̒P���T���B�T���n�߂�ʒu��nIdx�Ŏw��B for �����L�[���[�h
	static bool SearchNextWordPosition4KW(
		const wchar_t*	pLine,
		CLogicInt		nLineLen,
		CLogicInt		nIdx,		//	����
		CLogicInt*		pnColmNew,	//	���������ʒu
		BOOL			bStopsBothEnds	//	�P��̗��[�Ŏ~�܂�
	);


	template< class CHAR_TYPE >
	static int GetWord( const CHAR_TYPE*, const int, const CHAR_TYPE *pszSplitCharList,
		CHAR_TYPE **ppWordStart, int *pnWordLen );

protected:

	static bool _match_charlist( const ACHAR c, const ACHAR *pszList );
	static bool _match_charlist( const WCHAR c, const WCHAR *pszList );
};

BOOL IsURL( const wchar_t*, int, int* );/* �w��A�h���X��URL�̐擪�Ȃ��TRUE�Ƃ��̒�����Ԃ� */
BOOL IsMailAddress( const wchar_t*, int, int* );	/* ���݈ʒu�����[���A�h���X�Ȃ�΁ANULL�ȊO�ƁA���̒�����Ԃ� */



// ACHAR ��
inline bool CWordParse::_match_charlist( const ACHAR c, const ACHAR *pszList )
{
	for( int i = 0; pszList[i] != '\0'; i++ ){
		if( pszList[i] == c ){ return true; }
	}
	return false;
}
// WCHAR ��
inline bool CWordParse::_match_charlist( const WCHAR c, const WCHAR *pszList )
{
	for( int i = 0; pszList[i] != L'\0'; i++ ){
		if( pszList[i] == c ){ return true; }
	}
	return false;
}

/*!
	@param [in] pS					������o�b�t�@
	@param [in] nLen				������o�b�t�@�̒���
	@param [in] pszSplitCharList	��؂蕶������
	@param [out] ppWordStart		�P��̊J�n�ʒu
	@param [out] pnWordLen			�P��̒���

	@return �ǂ񂾃f�[�^�̒����B
*/
template< class CHAR_TYPE >
int CWordParse::GetWord( const CHAR_TYPE *pS, const int nLen, const CHAR_TYPE *pszSplitCharList,
	CHAR_TYPE **ppWordStart, int *pnWordLen )
{
	const CHAR_TYPE *pr = pS;
	CHAR_TYPE *pwordstart;
	int nwordlen;

	if( nLen < 1 ){
		pwordstart = const_cast<CHAR_TYPE *>(pS);
		nwordlen = 0;
		goto end_func;
	}

	// ��؂蕶�����X�L�b�v
	for( ; pr < pS + nLen; pr++ ){
		// ��؂蕶���łȂ������̊ԃ��[�v
		if( !_match_charlist(*pr, pszSplitCharList) ){
			break;
		}
	}
	pwordstart = const_cast<CHAR_TYPE*>(pr);   // �P��̐擪�ʒu���L�^

	// �P����X�L�b�v
	for( ; pr < pS + nLen; pr++ ){
		// ��؂蕶��������܂Ń��[�v
		if( _match_charlist(*pr, pszSplitCharList) ){
			break;
		}
	}
	nwordlen = pr - pwordstart;  // �P��̒������L�^

end_func:
	if( ppWordStart ){
		*ppWordStart = pwordstart;
	}
	if( pnWordLen ){
		*pnWordLen = nwordlen;
	}
	return pr - pS;
}

#endif /* SAKURA_CWORDPARSE_6C07A5B6_49DE_430F_A56F_9F2B003214FC9_H_ */
/*[EOF]*/