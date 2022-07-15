using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PPEnemy : MonoBehaviour
{
    enum tagAni
    {
        Ani_Stand = 1,
        Ani_Dam = 4,
        Ani_Die = 5
    }

    private Animator m_oAnim;
    private AnimatorStateInfo m_oAnimInfo;
    private int m_nLastLife;
    private tagAni m_tagCurAni;//��ǰ����

    public int life;

    void FixedUpdate()
    {
        //��ֹ���巴��
        gameObject.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);
    }

    void DieAni()
    {
        if (life <= 0)
        {
            //����ֵС��0 ������������
            m_tagCurAni = tagAni.Ani_Die;
        }
    }

    void DamageAni()
    {
        if (life > 0)
        {
            m_oAnimInfo = m_oAnim.GetCurrentAnimatorStateInfo(0);
            if (m_oAnimInfo.IsTag("Damage"))
            {
                m_tagCurAni = tagAni.Ani_Stand;
                return;
            }

            if (m_nLastLife != life)
            {
                m_tagCurAni = tagAni.Ani_Dam;
            }
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        m_oAnim = GetComponent<Animator>();
        m_nLastLife = life;
        m_tagCurAni = tagAni.Ani_Stand;
    }

    // Update is called once per frame
    void Update()
    {
        DieAni();
        DamageAni();
        m_nLastLife = life;
        m_oAnim.SetInteger("animation", (int)m_tagCurAni);
    }
}
