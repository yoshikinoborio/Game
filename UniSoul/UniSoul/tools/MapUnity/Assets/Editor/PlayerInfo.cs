using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class PlayerInfo : EditorWindow
{
    //[MenuItem("Window/オブジェクトの配置情報 出力")]
    public static void ShowWindow()
    {
        //マップ上に配置されたプレイヤーを取得。
        GameObject Player = GameObject.Find("Player");
        //Playerがマップにいなかったらエラーをログに出力する。
        if (Player == null)
        {
            Debug.Log("Playerがいません。");
        }
        //プレイヤーのTransformを取得。
        Transform[] Players = Player.GetComponents<Transform>();

        string headerTxt = "";
        //foreachはコレクション(配列、リスト、辞書)のすべての要素を1回ずつ読み出す構文。
        foreach (Transform tr in Players)
        {
            if (tr.gameObject == Player)
                headerTxt += string.Format("//{0}\n", tr.name);
            headerTxt += "{\n";
            headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.position.x, tr.position.y, tr.position.z);
            headerTxt += string.Format("\tD3DXQUATERNION({0:f}, {1:f}f, {2:f}f, {3:f}f ),    //回転\n", tr.rotation.x, tr.rotation.y, tr.rotation.z, tr.rotation.w);
            headerTxt += "},\n";
        }

        StreamWriter sw = new StreamWriter("C:/Github/Game/UniSoul/UniSoul/PlayerInfo.h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }
}
