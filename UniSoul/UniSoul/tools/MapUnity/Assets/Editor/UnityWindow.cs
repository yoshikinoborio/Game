using UnityEngine;
using UnityEditor;
using System.Collections;

class UnityWindow : EditorWindow
{

    [MenuItem("Window/ヘッダー出力")]
    public static void ShowWindow()
    {
        EditorWindow.GetWindow(typeof(UnityWindow));
    }

    void OnGUI()
    {
        // The actual window code goes here
        GUILayout.Label("マップ上のオブジェクトの配置情報", EditorStyles.boldLabel);


        //オブジェクトの配置情報のボタンが押されtureが返って来る。
        if (GUILayout.Button("マップオブジェクトの配置情報 出力"))
        {
            //配置情報出力の処理
            MapObjectInfo.ShowWindow();
            Debug.Log("マップオブジェクトの配置情報が無事出力できました。");
        }

        //エネミーの配置情報のボタンが押されtureが返って来る。
        if (GUILayout.Button("エネミーの配置情報 出力"))
        {
            //エネミー配置情報出力の処理
            EnemyPosInfo.ShowWindow();
            Debug.Log("エネミーの配置情報が無事出力できました。");
        }

        //プレイヤーの配置情報のボタンが押されtureが返って来る。
        if (GUILayout.Button("プレイヤーの配置情報 出力"))
        {
            //プレイヤー配置情報出力の処理
            PlayerInfo.ShowWindow();
            Debug.Log("プレイヤーの配置情報が無事出力できました。");
        }

        //敵のコース定義の配置情報のボタンが押されtureが返って来る。
        if (GUILayout.Button("敵のコース定義の配置情報 出力"))
        {
            //敵のコース定義配置情報出力の処理
            EnemyCourse.ShowWindow();
            Debug.Log("敵のコース定義の配置情報が無事出力できました。");
        }
        //コリジョンの配置情報のボタンが押されtureが返って来る。
        if (GUILayout.Button("コリジョンの配置情報 出力"))
        {
            //コリジョンの配置情報出力の処理
            Collition.ShowWindow();
            Debug.Log("コリジョンの配置情報が無事出力できました。");
        }
    }
}
