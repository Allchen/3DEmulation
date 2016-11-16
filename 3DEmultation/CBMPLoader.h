//======================================================================
/**
*  @file      CBMPLoader.h
*
*  ��Ŀ������ ���������
*  �ļ�����:  ����λͼ�� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-11-23	
*  �޸����ڣ� 2006-11-26
*	
*/																			
//======================================================================

#ifndef __CBMPLOADER_H__
#define __CBMPLOADER_H__

#include<windows.h>        /**< ����windows.h�ļ� */
#include<stdio.h>          /**< ����stdio.h�ļ� */

#define BITMAP_ID 0x4D42	/**< λͼ�ļ��ı�־ */

/** λͼ������ */
class CBMPLoader
{
   public:
      CBMPLoader();
      ~CBMPLoader();

      bool LoadBitmap(char *filename); /**< װ��һ��bmp�ļ� */
      void FreeImage();                /**< �ͷ�ͼ������ */

      unsigned int ID;                 /**< ���������ID�� */
      int imageWidth;                  /**< ͼ���� */
      int imageHeight;                 /**< ͼ��߶� */
      unsigned char *image;            /**< ָ��ͼ�����ݵ�ָ�� */
};

#endif //__CBMPLOADER_H__

