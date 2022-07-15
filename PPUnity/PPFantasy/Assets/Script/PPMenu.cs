using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PPMenu : MonoBehaviour
{
    [SerializeField]
    private GameObject menu;

    // Start is called before the first frame update
    void Start()
    {
        menu.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if(gameObject.GetComponent<PPObjMove>().IsEsc())
        {
            menu.SetActive(true);
        }
        else
        {
            menu.SetActive(false);
        }
    }
}
