using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PPObjAtk : MonoBehaviour
{
    [SerializeField]
    private GameObject target;

    private void OnTriggerEnter(Collider collider)
    {
        //µ±Ç°×´Ì¬Îª¹¥»÷
        if(target.GetComponent<PPObjMove>().IsAttack())
        {
            if (collider.tag == "Enemy")
            {
                GameObject m_oTarget = collider.gameObject;
                m_oTarget.GetComponent<PPEnemy>().life -= 10;
            }     
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
