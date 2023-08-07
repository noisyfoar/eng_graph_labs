#include "pipeline.h"


const Matrix4f* Pipeline::GetTrans()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans, CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
    RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
    TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);
    CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
    CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
    PersProjTrans.InitPersProjTransform(m_persProj.FOV, m_persProj.Width, m_persProj.Height, m_persProj.zNear, m_persProj.zFar);

    m_transformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * TranslationTrans * RotateTrans * ScaleTrans;
    return &m_transformation;
}
/*
После завершения мировых преобразований (комбинация масштабирования, вращения и перемещения объекта),
мы начинаем преобразования камеры 'движением' ее обратно в начало координат. 
Это делается смещением на обратный вектор позиции камеры.
Поэтому если камера находится в точке (1,2,3), мы двигаем объекты на (-1,-2,-3).
После этого мы генерируем вращение камеры, основываясь на направлении камеры и ее векторе вверх. 
На этом участие камеры завершено.
В конце мы проецируем координаты.
*/
