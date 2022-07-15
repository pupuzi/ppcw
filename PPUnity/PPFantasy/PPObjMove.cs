using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//��ɫ����귽���ƶ�
public class PPObjMove : MonoBehaviour
{
    enum tagAni
    {
        Ani_Stand = 1,
        Ani_Walk = 6,
        Ani_Run = 10,
        Ani_Atk1 = 21,
        Ani_Atk3 = 23
    }

    private Animator m_oAnim;
    private AnimatorStateInfo m_oAnimInfo;
    private tagAni m_tagCurAni;//��ǰ����
    private bool m_bIsEsc;

    private float m_fInputH;
    private float m_fInputV;

    [SerializeField]
    private Camera targetCamera;

    public void SetEsc(bool bIsEsc)
    {
        m_bIsEsc = bIsEsc;
    }

    public bool IsEsc()
    {
        return m_bIsEsc;
    }

    void FixedUpdate()
    {
        //��ֹ���巴��
        gameObject.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);
    }

    public bool IsAttack()
    {
        m_oAnimInfo = m_oAnim.GetCurrentAnimatorStateInfo(0);
        if (m_oAnimInfo.IsTag("Attack"))
        {
            return true;
        }
        return false;
    }

    void Move()
    {
        if(m_tagCurAni == tagAni.Ani_Atk1 || m_tagCurAni == tagAni.Ani_Atk3)
        {
            //��ǰ�����ǹ���
            return;
        }

        m_oAnim.SetBool("bIsRun", Input.GetKey(KeyCode.LeftShift)); //����Ƿ��ܲ�

        m_fInputH = Input.GetAxis("Horizontal");
        m_fInputV = Input.GetAxis("Vertical");

        m_oAnim.SetFloat("fInputH", m_fInputH);
        m_oAnim.SetFloat("fInputV", m_fInputV);

        var dx = 2 * gameObject.transform.position.x - targetCamera.transform.position.x;
        var dz = 2 * gameObject.transform.position.z - targetCamera.transform.position.z;

        float fX = m_fInputH / 1;
        float fZ = m_fInputV / 1;

        float fDx = dx - gameObject.transform.position.x;
        float fDz = dz - gameObject.transform.position.z;

        double cosx = fDz / System.Math.Sqrt(fDx * fDx + fDz * fDz);
        double sinx = fDx / System.Math.Sqrt(fDx * fDx + fDz * fDz);

        if (m_fInputV > 0.1 || m_fInputV < -0.1 || m_fInputH > 0.1 || m_fInputH < -0.1)
        {
            long nRun = 1;
            if (m_oAnim.GetBool("bIsRun"))
            {
                nRun = 2;
                m_tagCurAni = tagAni.Ani_Run;
            }
            else
            {
                m_tagCurAni = tagAni.Ani_Walk;
            }
            gameObject.transform.LookAt(gameObject.transform.position + new Vector3((float)(fZ * sinx + fX * cosx), 0, (float)(fZ * cosx - fX * sinx)));
            gameObject.transform.Translate(new Vector3((float)(fZ * sinx + fX * cosx) * nRun, 0, (float)(fZ * cosx - fX * sinx) * nRun) * Time.deltaTime, Space.World);
        }
        else
        {
            m_tagCurAni = tagAni.Ani_Stand;
        }
    }

    void InitGameStatus()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            m_bIsEsc = !m_bIsEsc;
        }
        Cursor.visible = m_bIsEsc;
    }

    void InitAction()
    {
        //�жϵ�ǰ����
        m_oAnimInfo = m_oAnim.GetCurrentAnimatorStateInfo(0);
        if (m_oAnimInfo.IsTag("Attack"))
        {
            //���������Ѿ�����
            m_tagCurAni = tagAni.Ani_Stand;
            return;
        }
        //���﹥������
        if (Input.GetMouseButtonDown(0))
        {
            m_tagCurAni = tagAni.Ani_Atk1;
            gameObject.GetComponent<PPObjRole>().m_nMagic -= 10;//��������-���Կ�ű�����
            return;
        }
        if (Input.GetMouseButtonDown(1))
        {
            m_tagCurAni = tagAni.Ani_Atk3;
            gameObject.GetComponent<PPObjRole>().m_nMagic -= 10;
            return;
        }
        //�����ƶ�����
        Move();
    }

    // Start is called before the first frame update
    void Start()
    {
        m_bIsEsc = false;
        Cursor.visible = false;
        m_oAnim = GetComponent<Animator>();
        m_tagCurAni = tagAni.Ani_Stand;
    }

    // Update is called once per frame
    void Update()
    {
        //��ʼ����Ϸ״̬
        InitGameStatus();
        if (m_bIsEsc)
        {
            //��ǰ��Ϸ��ͣ
            return;
        }
        //��ʼ������
        InitAction();
        //���ö���
        m_oAnim.SetInteger("animation", (int)m_tagCurAni);
    }
}
