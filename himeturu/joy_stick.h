#ifndef _INC_JOYSTICK
#define _INC_JOYSTICK

#include "arduino.h"

#define AXHISTORYNUM 10	//�ǂꂾ���̗������c����

//xy����\��
typedef struct axis{
    int x;
    int y;
};
//�W���C�X�e�B�b�N�̍ŏ��C�����C�ő��\��
typedef struct axismap {
	int max;
	int center;
	int min;
};
//axismap��xy�����Z�b�g�ɂ�������
typedef struct mapxy {
	axismap x;
	axismap y;
};

//�W���C�X�e�B�b�N�Ɋւ���N���X
class JoyStick {
private:

    int xpin, ypin;					//�W���C�X�e�B�b�N�̌q�����Ă���s���ԍ�
    axis axhistory[AXHISTORYNUM];	//�W���C�X�e�B�b�N�̃A�i���O�l
	mapxy posmap;					//�W���C�X�e�B�b�N�͈̔�

public:

	/// <summary>
	/// �C���X�^���X�������ɌĂ΂��
	/// </summary>
	/// <param name="x">X���̃s���ԍ�</param>
	/// <param name="y">y���̃s���ԍ�</param>
    JoyStick(int x, int y);
	/// <summary>
	/// �A�i���O�l���擾����
	/// </summary>
	/// <param name="all">���������ׂčX�V���邩</param>
	/// <returns>���݂̃A�i���O�l��Ԃ�</returns>
    axis read(boolean all);
	/// <summary>
	/// ���݂̃X�e�B�b�N�ʒu���擾����
	/// </summary>
	/// <returns>-100�`100�͈̔́i�W���C�X�e�B�b�N������0�j</returns>
    axis getPosition();
	/// <summary>
	/// RC�t�B���^�����������݂̃X�e�B�b�N�ʒu���擾����
	/// </summary>
	/// <param name="a">RC�t�B���^�̋��x�i0�`0.99�C����0.9�j</param>
	/// <returns>-100�`100�͈̔́i�W���C�X�e�B�b�N������0�j</returns>
    axis getPositionRCFilter(double a);
	/// <summary>
	/// �ړ����σt�B���^�����������݂̃X�e�B�b�N�ʒu���擾����
	/// </summary>
	/// <returns>-100�`100�͈̔́i�W���C�X�e�B�b�N������0�j</returns>
    axis getPositionAveFilter();
	/// <summary>
	/// �֐����s���̃X�e�B�b�N��Ԃ𒆉��l�Ƃ��C�ő�l�C�ŏ��l���v�Z����
	/// </summary>
	/// <returns>�����l��400�̏ꍇ�C�ŏ��l�P�C�ő�l799�ƂȂ�i�A�i���O�l��0�`1023�̏ꍇ�j</returns>
	mapxy setCenterPosition();
	/// <summary>
	/// setCenterPosition�̌v�Z���ʂ����Ƃ�-100�`100�͈̔͂ɕϊ�����
	/// </summary>
	/// <param name="axin">�A�i���O�l</param>
	/// <returns>-100�`100�͈̔́i�W���C�X�e�B�b�N������0�j</returns>
	axis joymap(axis axin);

};

#endif
