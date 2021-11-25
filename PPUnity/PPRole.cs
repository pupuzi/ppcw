using CPPUnity;
using System;
using UnityEngine;

namespace CPPUnity
{
    public class CPPRole : MonoBehaviour
    {
        //类绑定的角色
        private GameObject m_oRole;
        private CPPRoleProperty m_oProperty;
        private Transform m_oUserCamera;
        private void Start()
        {
            m_oRole = gameObject;
        }
        private void Update()
        {
            m_oRole.transform.Translate(m_oProperty.UpdateMove(m_oUserCamera) * Time.deltaTime, Space.Self);
        }
        public void Control()
        {

        }
        public void Attach(Animator role)
        {
            m_oRole = role;
        }
        public void Attach(Transform camera)
        {
            m_oUserCamera = camera;
        }
    }

    public class CPPRoleProperty
    {
        private CPPRoleStatus m_oStatus;
        private CPPRolePosition m_oPos;
        
        public Vector3 UpdateMove(Transform camera)
        {
           return m_oPos.GetRealMove(camera);
        }
    }
    public class CPPRolePosition
    {
        private float m_fMoveX = 0;
        private float m_fMoveY = 0;
        private float m_fMoveZ = 0;
        public float m_fXMoveSpeed = 1;
        public float m_fZMoveSpeed = 1;
        public float m_fYMoveSpeed = 1;
        public Vector3 GetRealMove(Transform camera)
        {
            //以场景坐标为基准
            //将用户镜头方向平面化,方便分解
            Vector3 oUserAxis = camera.forward;
            float fDXZ = (float)Math.Round(Math.Pow(oUserAxis[0], 2.0) + Math.Pow(oUserAxis[2], 2.0), 2);
            float fCosXZ = oUserAxis[0] / fDXZ;
            float fSinXZ = oUserAxis[2] / fDXZ;
            //分解方向speed
            m_fMoveX = m_fXMoveSpeed * fCosXZ + m_fZMoveSpeed * fSinXZ;
            m_fMoveZ = m_fXMoveSpeed * fSinXZ + m_fZMoveSpeed * fCosXZ;
            m_fMoveY = m_fYMoveSpeed;
            return new Vector3(m_fMoveX, m_fMoveY, m_fMoveZ);
        }
    }
    public class CPPRoleStatus
    {
        private long m_nLife;
        private long m_nMana;
        private long m_nPhy;
        private long m_nMaxLife;
        private long m_nMaxMana;
        private long m_nMaxPhy;
        public void Update(long nDLife, long nDMana, long nDPhy)
        {
            m_nLife = (m_nLife + nDLife >= m_nMaxLife) ? (m_nLife = m_nMaxLife) : (m_nLife += nDLife);
            m_nMana = (m_nMana + nDMana >= m_nMaxMana) ? (m_nMana = m_nMaxMana) : (m_nLife += nDMana);
            m_nPhy = (m_nPhy + nDPhy >= m_nMaxPhy) ? (m_nPhy = m_nMaxPhy) : (m_nLife += nDPhy);
        }
        public void UpdateMax(long nDLife, long nDMana, long nDPhy)
        {
            m_nMaxLife += nDLife;
            m_nMaxMana += nDMana;
            m_nMaxPhy += nDPhy;
        }
    }
}
