#pragma once

/// 列挙子管理

/// <summary>
/// オブジェクトタイプ
/// </summary>
enum ObjectType {

	TypeNone,
	TypePlayer,
	TypeEnemy,
	TypePlayerBullet,
	TypeEnemyBullet,

};

/// <summary>
/// オブジェクトのタグ
/// </summary>
enum ObjectTag {

	TagNone, // 何にも属さない
	TagPlayer, // プレイヤー
	TagEnemy, // 敵

};

/// <summary>
/// 衝突判定タイプ
/// </summary>
enum collisionType {

	CollisionNone, // 当たり判定を検証しない
	CollisionSphere // 球

};

/// <summary>
/// エフェクト種類
/// </summary>
enum ParticleType {

	ParticleDefault, // パーティクルを再生しない

};

/// <summary>
/// スプライト種類
/// </summary>
enum SpriteType {

	SpriteNone, // スプライトを表示しない
	SpriteReticle, // プレイヤーの照準

};

/// <summary>
/// 演出
/// </summary>
enum WayPoint {
	WayPoint1,
	WayPoint2,
	WayPoint3,
	WayPoint4,
	WayPoint5,
};