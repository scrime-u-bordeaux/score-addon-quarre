#pragma once

#include <quarre/mapping/quarre-mapping.hpp>
#include <quarre/device/quarre-device.hpp>
#include <score/model/IdentifiedObject.hpp>
#include <quarre/process/quarre-process-model.hpp>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>

namespace score     {
namespace addons    {
namespace quarre    {

class user;
class InspectorWidget;

class interaction final : public IdentifiedObject<interaction>
{
    Q_OBJECT
    SCORE_SERIALIZE_FRIENDS

    friend class quarre::ProcessModel;
    friend class quarre::mapping;

    public: //-----------------------------------------------------
    interaction ( const Id<interaction>& id, QObject* parent );

    template <typename impl> interaction(impl& vis, QObject* parent) :
        IdentifiedObject(vis, parent)
    {
        vis.writeTo(*this);
    }

    const QString module        () const;
    const QString title         () const;
    const QString description   () const;
    int length                  () const;
    int countdown               () const;

    std::vector<ossia::value> to_list() const;

    QStringList inputs()    const;
    const std::vector<quarre::mapping*>& mappings();

    signals:
    void mapping_added      ( quarre::mapping& mapping );
    void mapping_removed    ( quarre::mapping& mapping );

    public slots: //-----------------------------------------------
    void onModuleChanged            ( QString module );
    void onTitleChanged             ( QString title );
    void onDescriptionChanged       ( QString description );
    void onLengthChanged            ( int length );
    void onCountdownChanged         ( int countdown );

    void on_mapping_added          ( );
    void on_mapping_removed        ( quarre::mapping* mapping );

    private:  //---------------------------------------------------
    QString         m_module;
    QString         m_title;
    QString         m_description;
    int             m_length;
    int             m_countdown;

    quarre::InspectorWidget* m_inspector;

    std::shared_ptr<quarre::user> m_host;
    std::vector<quarre::mapping*> m_mappings;
};

}
}
}
