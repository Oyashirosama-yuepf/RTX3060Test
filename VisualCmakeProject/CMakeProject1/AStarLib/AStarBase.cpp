#include "iostream"
#include "AStarBase.h"


CAStarBase::CAStarBase()
{
	m_pAPointArr = NULL;
	m_nAPointArrWidth = 0;
	m_nAPointArrHeight = 0;

	m_pStartPoint = NULL;
	m_pEndPoint = NULL;
	m_pCurPoint = NULL;

}

CAStarBase::~CAStarBase()
{

}

BOOL CAStarBase::Create(char* pDateArr, int nWidth, int nHeight)
{
	if (!pDateArr) return FALSE;
	if (nWidth < 1 || nHeight < 1) return FALSE;
	m_pAPointArr = new APoint[nWidth * nHeight];
	if (!m_pAPointArr) return FALSE;
	m_pOldArr = pDateArr;
	m_nAPointArrWidth = nWidth;
	m_nAPointArrHeight = nHeight;
	// 初始化数组内容
	for (int y = 0; y < m_nAPointArrHeight; y++)
	{
		for (int x = 0; x < m_nAPointArrWidth; x++)
		{
			m_pAPointArr[y * m_nAPointArrWidth + x].x = x;
			m_pAPointArr[y * m_nAPointArrWidth + x].y = y;
			m_pAPointArr[y * m_nAPointArrWidth + x].g = 0;
			m_pAPointArr[y * m_nAPointArrWidth + x].f = 0;
			m_pAPointArr[y * m_nAPointArrWidth + x].h = 0;

			if (pDateArr[y * m_nAPointArrWidth + x] == '0')
			{
				m_pAPointArr[y * m_nAPointArrWidth + x].type = APT_OPENED;
			}
			else if (pDateArr[y * m_nAPointArrWidth + x] == '1')
			{
				m_pAPointArr[y * m_nAPointArrWidth + x].type = APT_CLOSED;
			}
			else if (pDateArr[y * m_nAPointArrWidth + x] == 'S')
			{
				m_pAPointArr[y * m_nAPointArrWidth + x].type = APT_STARTPOINT;
				m_pStartPoint = m_pAPointArr + y * m_nAPointArrWidth + x;
				m_pCurPoint = m_pStartPoint;
			}
			else if (pDateArr[y * m_nAPointArrWidth + x] == 'E')
			{
				m_pAPointArr[y * m_nAPointArrWidth + x].type = APT_ENDPOINT;
				m_pEndPoint = m_pAPointArr + y * m_nAPointArrWidth + x;
			}
			else {
				m_pAPointArr[y * m_nAPointArrWidth + x].type = APT_UNKNOWN;
			}

		}
	}
	return TRUE;
}

void CAStarBase::SetStartPoint(int x, int y)
{
	if (m_pStartPoint && m_pAPointArr[y * m_nAPointArrWidth + x].type != APT_CLOSED)
	{
		m_pStartPoint->type = APT_OPENED;
		// 设置新的值
		m_pStartPoint = m_pAPointArr + y * m_nAPointArrWidth + x;
		m_pStartPoint->type = APT_STARTPOINT;
		m_pCurPoint = m_pStartPoint;
	}
}

void CAStarBase::SetEndPoint(int x, int y)
{
	if (m_pStartPoint && m_pAPointArr[y * m_nAPointArrWidth + x].type != APT_CLOSED)
	{
		m_pStartPoint->type = APT_OPENED;
		// 设置新的值
		m_pStartPoint = m_pAPointArr + y * m_nAPointArrWidth + x;
		m_pStartPoint->type = APT_ENDPOINT;
	}
}

void CAStarBase::SetCurrent(int x, int y)
{
	//	if ( m_pAPointArr[y*m_nAPointArrWidth+x].type==APT_OPENED )
	{
		m_pCurPoint = m_pAPointArr + y * m_nAPointArrWidth + x;
	}
}

void CAStarBase::SetOpened(int x, int y)
{
	if (m_pAPointArr[y * m_nAPointArrWidth + x].type != APT_OPENED)
	{
		m_pAPointArr[y * m_nAPointArrWidth + x].type = APT_OPENED;
	}
}

void CAStarBase::SetClosed(int x, int y)
{
	if (m_pAPointArr[y * m_nAPointArrWidth + x].type != APT_CLOSED)
	{
		m_pAPointArr[y * m_nAPointArrWidth + x].type = APT_CLOSED;
	}
}

void CAStarBase::PrintCharArr()
{
	if (m_pOldArr)
	{
		for (int y = 0; y < m_nAPointArrHeight; y++)
		{
			for (int x = 0; x < m_nAPointArrWidth; x++)
			{
				printf("%c ", m_pOldArr[x + m_nAPointArrWidth * y]);
			}
			printf("\r\n");
		}
		printf("\r\n");
	}
}

PAPoint CAStarBase::CalcNextPoint(PAPoint ptCalc)
{
	if (ptCalc == NULL)
	{
		ptCalc = m_pStartPoint;
	}
	int x = ptCalc->x;
	int y = ptCalc->y;
	int dx = m_pEndPoint->x;
	int dy = m_pEndPoint->y;
	int xmin = x, ymin = y, vmin = 0; // 最优步骤的坐标和值
	// 判断是否已经到了最终的位置
	if ((x == dx && abs(y - dy) == 1) || (y == dy && abs(x - dx) == 1))
	{
		return m_pEndPoint;
	}
	// 上
	if (m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].type == APT_OPENED && y > 0)
	{
		m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].g = 10;
		m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].h =
			10 * (abs(x - dx) + abs(y - 1 - dy));
		m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].f =
			m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].g + m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].h;
		if (vmin == 0)
		{
			xmin = x;
			ymin = y - 1;
			vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].f;
		}
		else {
			if (vmin > m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].f)
			{
				xmin = x;
				ymin = y - 1;
				vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y - 1)].f;
			}
		}
	}
	// 下
	if (m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].type == APT_OPENED && y < m_nAPointArrHeight)
	{
		m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].g = 10;
		m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].h =
			10 * (abs(x - dx) + abs(y + 1 - dy));
		m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].f =
			m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].g + m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].h;
		if (vmin == 0)
		{
			xmin = x;
			ymin = y + 1;
			vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].f;
		}
		else {
			if (vmin > m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].f)
			{
				xmin = x;
				ymin = y + 1;
				vmin = m_pAPointArr[(x + 0) + m_nAPointArrWidth * (y + 1)].f;
			}
		}
	}
	// 左
	if (m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].type == APT_OPENED && x > 0)
	{
		m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].g = 10;
		m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].h =
			10 * (abs(x - 1 - dx) + abs(y - dy));
		m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].f =
			m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].g + m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].h;
		if (vmin == 0)
		{
			xmin = x - 1;
			ymin = y;
			vmin = m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].f;
		}
		else {
			if (vmin > m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].f)
			{
				xmin = x - 1;
				ymin = y;
				vmin = m_pAPointArr[(x - 1) + m_nAPointArrWidth * y].f;
			}
		}
	}
	// 右
	if (m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].type == APT_OPENED && x < m_nAPointArrWidth)
	{
		m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].g = 10;
		m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].h =
			10 * (abs(x + 1 - dx) + abs(y - dy));
		m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].f =
			m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].g + m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].h;
		if (vmin == 0)
		{
			xmin = x + 1;
			ymin = y;
			vmin = m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].f;
		}
		else {
			if (vmin > m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].f)
			{
				xmin = x + 1;
				ymin = y;
				vmin = m_pAPointArr[(x + 1) + m_nAPointArrWidth * y].f;
			}
		}
	}

	// 如果有最优点则迭代，则否就返回NULL
	if (vmin)
	{
		SetCurrent(xmin, ymin);
		SetClosed(xmin, ymin);
		*(m_pOldArr + xmin + m_nAPointArrWidth * ymin) = '-';
		PrintCharArr();
		PAPoint pApoint = CalcNextPoint(m_pCurPoint);
		if (pApoint == NULL)
		{
			SetCurrent(x, y);
			SetClosed(xmin, ymin);
			*(m_pOldArr + xmin + m_nAPointArrWidth * ymin) = '0';
			return CalcNextPoint(m_pCurPoint);
		}
		return pApoint;
	}
	else {
		return NULL;
	}

}