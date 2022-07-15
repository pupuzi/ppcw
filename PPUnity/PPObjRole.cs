using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PPObjRole : MonoBehaviour
{
    private Slider m_oSlider;

    [HideInInspector]
    public float m_nLife;

    [HideInInspector]
    public float m_nMagic;

    [SerializeField]
    private Image lifeImage;

    [SerializeField]
    private Image magicImage;

    // Start is called before the first frame update
    void Start()
    {
        m_nLife = 100;
        m_nMagic = 100;
    }

    // Update is called once per frame
    void Update()
    {
        m_oSlider = lifeImage.GetComponent<Slider>();
        m_oSlider.value = (100 - m_nLife) / 100;
        m_oSlider = magicImage.GetComponent<Slider>();
        m_oSlider.value = (100 - m_nMagic) / 100;
    }
}
