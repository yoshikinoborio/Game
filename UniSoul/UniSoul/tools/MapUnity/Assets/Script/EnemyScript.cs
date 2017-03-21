using UnityEngine;
using System.Collections;

public class EnemyScript : MonoBehaviour {
    public int enemyType = -1;
    public EnemyTypeText EnemyTypeText;
    // Use this for initialization
    void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}

[System.Serializable]
public class EnemyTypeText
{
    public int EnemySkeleton = 0;
    public int EnemyGoblin = 1;
    public int EnemyBoss = 2;
}
