using PPUnity;
using System;
using UnityEngine;

namespace CPPUnity
{
    public class CPPRole : MonoBehaviour
    {
        //类绑定的角色
        private Animator m_oRole;
        private CPPRoleProperty m_oProperty;
        private Transform m_oUserCamera;
        private void Start()
        {

        }
        private void Update()
        {
            m_oRole.transform.Translate(m_oProperty.GetRealMove(m_oUserCamera) * Time.deltaTime, Space.Self);
        }
        public void Control()
        {

        }
        public void Attach(Animator role)
        {
            m_oRole = role;
        }
    }

    public class CPPRoleProperty
    {
        private float m_fMoveX;
        private float m_fMoveY;
        private float m_fMoveZ;
        public float m_fXMoveSpeed = 1;
        public float m_fZMoveSpeed = 1;
        public Vector3 GetRealMove(Transform oUserCamera)
        {
            //以场景坐标为基准
            //将用户镜头方向平面化,方便分解
            Vector3 oUserAxis = oUserCamera.forward;
            float fDXZ = (float)Math.Round(Math.Pow(oUserAxis[0], 2.0) + Math.Pow(oUserAxis[2], 2.0), 2);
            float fCosXZ = oUserAxis[0] / fDXZ;
            float fSinXZ = oUserAxis[2] / fDXZ;
            //分解方向speed
            m_fMoveX = m_fXMoveSpeed * fCosXZ + m_fZMoveSpeed * fSinXZ;
            m_fMoveZ = m_fXMoveSpeed * fSinXZ + m_fZMoveSpeed * fCosXZ;
            return new Vector3(m_fMoveX, m_fMoveY, m_fMoveZ);
        }
    }
}
