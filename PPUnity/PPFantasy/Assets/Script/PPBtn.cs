using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PPBtn : MonoBehaviour
{
    [SerializeField]
    private GameObject player;

    [SerializeField]
    private GameObject menu;

    public void OnCancelClicked()
    {
        menu.SetActive(false);
        player.GetComponent<PPObjMove>().SetEsc(false);
    }

    public void OnOKClicked()
    {
        Application.Quit();
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
